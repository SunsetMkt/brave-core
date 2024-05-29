/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import { Locale, LocaleContext } from '../../shared/lib/locale_context'

export const localeStrings = {
  appErrorTitle: 'Something went wrong',
  cancelButtonLabel: 'Cancel',
  closeButtonLabel: 'Close',
  continueButtonLabel: 'Continue',
  countrySelectPlaceholder: 'Select',
  countrySelectTitle: 'Select your region',
  countrySelectText: 'Select your region so we can show you the right options and ads for your region.',
  doneButtonLabel: 'Done',
  onboardingButtonLabel: 'Join Brave Rewards',
  onboardingErrorCountryDeclaredText: 'Unfortunately, there was an error while trying to set your country. Please try again.',
  onboardingErrorDisabledText: 'New signups for Brave Rewards are currently disabled in your region. However, you can always try again later. $1Learn more$2',
  onboardingErrorDisabledTitle: 'Brave Rewards not available',
  onboardingErrorText: 'Unfortunately, there was an error while trying to set up Brave Rewards. Please try again.',
  onboardingErrorTitle: 'Something went wrong',
  onboardingLearnMoreLabel: 'How does it work?',
  onboardingSuccessLearnMoreLabel: 'How does Brave Rewards work?',
  onboardingSuccessText: 'Now you can get rewarded for viewing ads. You’re helping make the web a better place for everyone. And that’s awesome!',
  onboardingSuccessTitle: 'Woohoo! You\'re all set!',
  onboardingTermsText: 'By enabling Rewards, you agree to the $1Terms of Service$2 and $3Privacy Policy$4.',
  onboardingTextItem1: 'Get paid for private ads you see in Brave',
  onboardingTextItem2: 'Get special benefits and discounts',
  onboardingTitle: 'Become a $1Brave Rewards member'
}

export type StringKey = keyof typeof localeStrings

export function useLocaleContext () {
  return React.useContext<Locale<StringKey>>(LocaleContext)
}

