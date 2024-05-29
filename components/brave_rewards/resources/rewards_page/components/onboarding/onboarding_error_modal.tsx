/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import Icon from '@brave/leo/react/icon'
import Button from '@brave/leo/react/button'

import { EnableRewardsResult } from '../../lib/app_model'
import { useLocaleContext } from '../../lib/locale_strings'
import { formatMessage } from '../../../shared/lib/locale_context'
import { Modal } from '../modal'
import { NewTabLink } from '../../../shared/components/new_tab_link'

import * as style from './onboarding_error_modal.style'
import * as urls from '../../../shared/lib/rewards_urls'

interface Props {
  result: EnableRewardsResult
  onClose: () => void
}

export function OnboardingErrorModal (props: Props) {
  const { getString } = useLocaleContext()

  if (props.result === 'success') {
    return null
  }

  function getResultMessages () {
    if (props.result === 'wallet-generation-disabled') {
      return {
        header: getString('onboardingErrorDisabledTitle'),
        text: formatMessage(getString('onboardingErrorDisabledText'), {
          tags: {
            $1: (content) =>
              <NewTabLink key='link' href={urls.walletCreationDisabledURL}>
                {content}
              </NewTabLink>
          }
        })
      }
    }

    if (props.result === 'country-already-declared') {
      return {
        header: getString('onboardingErrorTitle'),
        text: getString('onboardingErrorCountryDeclaredText')
      }
    }

    return {
      header: getString('onboardingErrorTitle'),
      text: getString('onboardingErrorText')
    }
  }

  const messages = getResultMessages()

  return (
    <Modal>
      <style.root>
        <style.icon>
          <Icon name='warning-circle-filled' />
        </style.icon>
        <style.title>
          {messages.header}
        </style.title>
        <style.text>
          {messages.text}
        </style.text>
        <style.action>
          <Button onClick={props.onClose}>
            {getString('closeButtonLabel')}
          </Button>
        </style.action>
        <style.errorCode>
          {props.result}
        </style.errorCode>
      </style.root>
    </Modal>
  )
}
