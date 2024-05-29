/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import Button from '@brave/leo/react/button'

import { TabOpenerContext , NewTabLink } from '../../../shared/components/new_tab_link'
import { useLocaleContext } from '../../lib/locale_strings'
import { Modal } from '../modal'

import * as urls from '../../../shared/lib/rewards_urls'
import * as style from './onboarding_success_modal.style'

interface Props {
  onClose: () => void
}

export function OnboardingSuccessModal (props: Props) {
  const tabOpener = React.useContext(TabOpenerContext)
  const { getString } = useLocaleContext()

  function onDoneClick () {
    tabOpener.openTab(urls.rewardsTourURL)
    props.onClose()
  }

  return (
    <Modal onBackdropClick={props.onClose}>
      <style.root>
        <style.successIcon />
        <style.title>
          {getString('onboardingSuccessTitle')}
        </style.title>
        <style.text>
          {getString('onboardingSuccessText')}
        </style.text>
        <style.action>
          <Button onClick={onDoneClick}>
            {getString('doneButtonLabel')}
          </Button>
        </style.action>
        <style.learnMore>
          <NewTabLink href={urls.rewardsTourURL}>
            {getString('onboardingSuccessLearnMoreLabel')}
          </NewTabLink>
        </style.learnMore>
      </style.root>
    </Modal>
  )
}
