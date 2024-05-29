/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import { color, font } from '@brave/leo/tokens/css/variables'

import background from '../../assets/onboarding_background.svg'
import backgroundDark from '../../assets/onboarding_background_dark.svg'

import rewardsLogoImage from '../../assets/rewards_logo.svg'
import rewardsLogoImageDark from '../../assets/rewards_logo_dark.svg'

export const root = styled.div`
  --onboarding-max-width: 392px;

  max-width: var(--onboarding-max-width);
  margin: 0 auto;
  padding: 53px 16px;
  background-image: url(${background});
  background-repeat: no-repeat;
  background-position: center 31px;
  background-size: 392px auto;
  display: flex;
  flex-direction: column;
  align-items: center;

  a {
    color: ${color.text.interactive};
  }

  @media (prefers-color-scheme: dark) {
    background-image: url(${backgroundDark});
  }
`

export const logo = styled.div`
  height: 34px;
  width: 100%;
  background-image: url(${rewardsLogoImage});
  background-repeat: no-repeat;
  background-position: center;
  background-size: auto 34px;

  @media (prefers-color-scheme: dark) {
    background-image: url(${rewardsLogoImageDark});
  }
`

export const batImage = styled.div`
  margin: 40px 0;

  img {
    height: 98px;
  }
`

export const header = styled.div`
  font: ${font.heading.h3};
  color: ${color.text.primary};
  white-space: pre-line;
  text-align: center;
`

export const text = styled.div`
  margin: 8px 0;
  padding: 16px 28px;
  display: flex;
  flex-direction: column;
  gap: 16px;
  font: ${font.default.regular};
  color: ${color.text.primary};

  > * {
    --leo-icon-size: 16px;
    display: flex;
    align-items: center;
    gap: 16px;
    letter-spacing: -0.1px;
  }
`

export const action = styled.div`
  display: flex;
  align-content: stretch;
  width: 100%;
`

export const learnMore = styled.div`
  margin: 12px 0 40px;
  font: ${font.components.buttonDefault};

  a {
    text-decoration: none;
  }
`

export const terms = styled.div`
  font: ${font.xSmall.regular};
  color: ${color.text.tertiary};
  text-align: center;

  a {
    white-space: pre;
  }
`
