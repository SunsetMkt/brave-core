/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import { color, font } from '@brave/leo/tokens/css/variables'

export const root = styled.div`
  max-width: var(--onboarding-max-width);
  display: flex;
  flex-direction: column;
  align-items: center;
  text-align: center;
`

export const icon = styled.div`
  margin: 48px 0 16px;
  --leo-icon-size: 24px;
  --leo-icon-color: ${color.systemfeedback.errorIcon};
`

export const title = styled.div`
  margin: 0 3px 0;
  font: ${font.heading.h3};
  color: ${color.text.primary};
`

export const text = styled.div`
  margin: 8px 3px 0 3px;
  color: ${color.text.secondary};
  font: ${font.default.regular};

  a {
    padding-left: 4px;
    text-decoration: underline;
  }
`

export const action = styled.div`
  width: 100%;
  margin-top: 24px;
  margin-bottom: 4px;
  display: flex;
  align-items: stretch;
`

export const errorCode = styled.div`
  margin-top: 12px;
  padding-bottom: 7px;
  color: ${color.text.tertiary};
  font: ${font.xSmall.regular};
`
