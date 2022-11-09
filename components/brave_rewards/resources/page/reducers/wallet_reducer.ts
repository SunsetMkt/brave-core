/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { Reducer } from 'redux'
import { types } from '../actions/rewards_types'

const walletReducer: Reducer<Rewards.State | undefined> = (state: Rewards.State, action) => {
  if (!state) {
    return
  }

  switch (action.type) {
    case types.GET_REWARDS_PARAMETERS:
      chrome.send('brave_rewards.getRewardsParameters')
      break
    case types.ON_REWARDS_PARAMETERS: {
      state = { ...state }
      state.parameters = action.payload.properties
      break
    }
    case types.ON_EXTERNAL_WALLET_PROVIDER_LIST: {
      if (!action.payload.list) {
        break
      }

      state = { ...state }
      state.externalWalletProviderList = action.payload.list
      break
    }
    case types.GET_BALANCE_REPORT: {
      chrome.send('brave_rewards.getBalanceReport', [
        action.payload.month,
        action.payload.year
      ])
      break
    }
    case types.ON_BALANCE_REPORT: {
      state = { ...state }
      state.balanceReport = action.payload.report
      break
    }
    case types.GET_CONTRIBUTION_AMOUNT: {
      chrome.send('brave_rewards.getContributionAmount')
      break
    }
    case types.ON_CONTRIBUTION_AMOUNT: {
      state = { ...state }
      state.contributionMonthly = action.payload.amount
      break
    }
    case types.GET_RECONCILE_STAMP: {
      chrome.send('brave_rewards.getReconcileStamp')
      break
    }
    case types.GET_PENDING_CONTRIBUTIONS: {
      chrome.send('brave_rewards.getPendingContributions')
      break
    }
    case types.ON_PENDING_CONTRIBUTIONS: {
      state = { ...state }
      state.pendingContributions = action.payload.list
      const total = state.pendingContributions
        .reduce((accumulator: number, item: Rewards.PendingContribution) => {
          return accumulator + item.amount
        }, 0)
      state.pendingContributionTotal = total
      break
    }
    case types.REMOVE_PENDING_CONTRIBUTION: {
      chrome.send('brave_rewards.removePendingContribution', [
        action.payload.id
      ])
      break
    }
    case types.REMOVE_ALL_PENDING_CONTRIBUTION: {
      chrome.send('brave_rewards.removeAllPendingContribution')
      break
    }
    case types.GET_BALANCE: {
      chrome.send('brave_rewards.fetchBalance')
      break
    }
    case types.ON_BALANCE: {
      const status = action.payload.status
      let ui = state.ui

      if (status === 0) { // on ledger::mojom::Result::LEDGER_OK
        state.balance = action.payload.balance
      } else if (status === 24) { // on ledger::type::Result::EXPIRED_TOKEN
        chrome.send('brave_rewards.getExternalWallet')
        state.balance.total = action.payload.balance.total || 0
      }

      state = {
        ...state,
        ui
      }
      break
    }
    case types.GET_EXTERNAL_WALLET: {
      chrome.send('brave_rewards.getExternalWallet')
      break
    }
    case types.GET_EXTERNAL_WALLET_PROVIDERS: {
      chrome.send('brave_rewards.getExternalWalletProviders')
      break
    }
    case types.SET_EXTERNAL_WALLET_TYPE: {
      chrome.send('brave_rewards.setExternalWalletType', [action.payload.provider])
      break
    }
    case types.ON_EXTERNAL_WALLET: {
      state = { ...state }

      if (action.payload.result === 24) { // type::Result::EXPIRED_TOKEN
        chrome.send('brave_rewards.getExternalWallet')
        break
      }

      if (action.payload.result === 9) { // type::Result::NOT_FOUND
        state.ui.modalRedirect = 'kycRequiredModal'
        break
      }

      if (action.payload.result === 25) { // type::Result::UPHOLD_BAT_NOT_ALLOWED
        state.ui.modalRedirect = 'upholdBATNotAllowedModal'
        break
      }

      if (action.payload.result === 36) { // type::Result::DEVICE_LIMIT_REACHED
        state.ui.modalRedirect = 'deviceLimitReachedModal'
        break
      }

      if (action.payload.result === 37) { // type::Result::MISMATCHED_PROVIDER_ACCOUNTS
        state.ui.modalRedirect = 'mismatchedProviderAccountsModal'
        break
      }

      if (action.payload.result === 41) { // type::Result::UPHOLD_TRANSACTION_VERIFICATION_FAILURE
        state.ui.modalRedirect = 'walletOwnershipVerificationFailureModal'
        break
      }

      if (action.payload.result === 43) { // type::Result::UPHOLD_INSUFFICIENT_CAPABILITIES
        state.ui.modalRedirect = 'upholdInsufficientCapabilitiesModal'
        break
      }

      if (action.payload.result === 44) { // type::Result::FLAGGED_WALLET
        state.ui.modalRedirect = 'flaggedWalletModal'
        break
      }

      if (action.payload.result === 45) { // type::Result::REGION_NOT_SUPPORTED
        state.ui.modalRedirect = 'regionNotSupportedModal'
        break
      }

      if (action.payload.result === 46) { // type::Result::MISMATCHED_COUNTRIES
        state.ui.modalRedirect = 'mismatchedCountriesModal'
        break
      }

      if (action.payload.result === 47) { // type::Result::PROVIDER_UNAVAILABLE
        state.ui.modalRedirect = 'providerUnavailableModal'
        break
      }

      if (action.payload.result === 0) { // type::Result::LEDGER_OK
        chrome.send('brave_rewards.fetchBalance')
      }

      state.externalWallet = action.payload.wallet
      break
    }
    case types.GET_MONTHLY_REPORT: {
      let month = action.payload.month
      let year = action.payload.year
      if (month == null) {
        month = new Date().getMonth() + 1
      }

      if (year == null) {
        year = new Date().getFullYear()
      }

      chrome.send('brave_rewards.getMonthlyReport', [month, year])
      break
    }
    case types.ON_MONTHLY_REPORT: {
      state = { ...state }
      state.monthlyReport = {
        month: action.payload.month,
        year: action.payload.year
      }

      if (!action.payload.report) {
        break
      }

      state.monthlyReport = Object.assign(state.monthlyReport, action.payload.report)
      break
    }
    case types.GET_MONTHLY_REPORT_IDS: {
      chrome.send('brave_rewards.getMonthlyReportIds')
      break
    }
    case types.ON_MONTHLY_REPORT_IDS: {
      state = { ...state }
      state.monthlyReportIds = action.payload
      break
    }
  }

  return state
}

export default walletReducer
