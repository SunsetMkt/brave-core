/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

import backgroundAnimated from '../assets/background_animated.svg'
import backgroundStatic from '../assets/background_static.svg'
import backgroundAnimatedDark from '../assets/background_animated_dark.svg'
import backgroundStaticDark from '../assets/background_static_dark.svg'

export const root = styled.div`
  &.is-bubble {
    width: 392px;
    min-height: 550px;
  }
`

export const background = styled.div`
  position: fixed;
  inset: 0;
  z-index: -1;
  background-image: url(${backgroundStatic});
  background-size: cover;

  .animated-background & {
    background-image: url(${backgroundAnimated});
  }

  @media (prefers-color-scheme: dark) {
    background-image: url(${backgroundStaticDark});

    .animated-background & {
      background-image: url(${backgroundAnimatedDark});
    }
  }
`

export const loading = styled.div`
  position: fixed;
  inset: 0 0 10% 0;
  display: flex;
  align-items: center;
  justify-content: center;
  opacity: 0;
  animation-name: app-loading-fade-in;
  animation-easing-function: ease-in-out;
  animation-duration: 500ms;
  animation-delay: 1.5s;
  animation-fill-mode: both;

  @keyframes app-loading-fade-in {
    from { opacity: 0; }
    to { opacity: 1; }
  }

  --leo-progressring-size: 32px
`
