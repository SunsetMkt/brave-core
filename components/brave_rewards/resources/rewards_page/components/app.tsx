/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import ProgressRing from '@brave/leo/react/progressRing'

import { AppModelContext, useAppState } from '../lib/app_model_context'

import { AppErrorBoundary } from './app_error_boundary'
import { Onboarding } from './onboarding/onboarding'
import { OnboardingSuccessModal } from './onboarding/onboarding_success_modal'

import * as style from './app.style'

export function App () {
  const model = React.useContext(AppModelContext)

  const [loading, openTime, embedder, paymentId] = useAppState((state) => [
    state.loading,
    state.openTime,
    state.embedder,
    state.paymentId
  ])

  React.useEffect(() => { model.onAppRendered() }, [model, openTime])

  const [showOnboardingSuccess, setShowOnboardingSuccess]
    = React.useState(false)

  function getComponentKey () {
    // This component key is used to reset the internal view state of the
    // component tree when the app is "reopened".
    return `rewards-page-${openTime}`
  }

  function getClassNames () {
    const list: string[] = []
    if (embedder.isBubble) {
      list.push('is-bubble')
    }
    if (embedder.animatedBackgroundEnabled) {
      list.push('animated-background')
    }
    return list.join(' ')
  }

  function renderModal () {
    if (showOnboardingSuccess) {
      const hideOnboardingCompleted = () => setShowOnboardingSuccess(false)
      return <OnboardingSuccessModal onClose={hideOnboardingCompleted} />
    }
    return null
  }

  function renderContent () {
    if (loading) {
      return (
        <style.loading>
          <ProgressRing />
        </style.loading>
      )
    }

    if (!paymentId) {
      const showOnboardingCompleted = () => setShowOnboardingSuccess(true)
      return <Onboarding onOnboardingCompleted={showOnboardingCompleted} />
    }

    return (
      <>
        {renderModal()}
      </>
    )
  }

  return (
    <style.root key={getComponentKey()} className={getClassNames()}>
      <AppErrorBoundary>
        {renderContent()}
      </AppErrorBoundary>
      <style.background />
    </style.root>
  )
}
