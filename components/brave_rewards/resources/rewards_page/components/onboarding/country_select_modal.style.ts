/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import { color, font } from '@brave/leo/tokens/css/variables'

import selectCaret from '../../assets/select_caret.svg'

export const root = styled.div`
  max-width: var(--onboarding-max-width);
  display: flex;
  flex-direction: column;
`

export const header = styled.div`
  padding: 4px 0 26px;
  display: flex;
  justify-content: flex-end;
`

export const graphic = styled.div`
  text-align: center;

  img {
    height: 145px;
  }
`

export const title = styled.div`
  margin: 16px 0;
  font: ${font.heading.h3};
  color: ${color.text.primary};
  text-align: center;
`

export const text = styled.div`
  margin: 16px 0;
  font: ${font.default.regular};
  color: ${color.text.secondary};
  text-align: center;
`

export const selector = styled.div`
  margin-bottom: 16px;

  select {
    -webkit-appearance: none;
    background:
      url(${selectCaret}) calc(100% - 12px) center no-repeat,
      ${color.container.highlight};
    background-size: 12px;
    width: 100%;
    border-radius: 8px;
    color: ${color.text.primary};
    font: ${font.default.regular};
    padding: 8px 36px 8px 11px;

    &.empty {
      color: ${color.text.secondary};
    }

    > option {
      color: ${color.text.primary};
      background: ${color.container.background};
    }
  }
`

export const actions = styled.div`
  display: flex;
  flex-direction: column;
  gap: 8px;
  align-items: stretch;
`
