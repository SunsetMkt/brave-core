/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'
import { color } from '@brave/leo/tokens/css/variables'

const breakpoint = '400px'

export const root = styled.div`
  --self-animation-duration: 200ms;

  .modal-skip-animations & {
    --self-animation-duration: 0;
  }

  position: fixed;
  top: 0;
  left: 0;
  bottom: 0;
  right: 0;
  overflow: auto;
  background: rgba(0, 0, 0, 0.15);
  backdrop-filter: blur(10px);
  z-index: 9999;
  display: flex;
  flex-direction: column;
  align-items: center;

  animation-name: modal-backdrop-fade;
  animation-easing-function: ease-out;
  animation-duration: var(--self-animation-duration);
  animation-fill-mode: both;

  @keyframes modal-backdrop-fade {
    from {
      background: rgba(0, 0, 0, 0);
      backdrop-filter: blur(0);
    }
    to {
      background: rgba(0, 0, 0, 0.15);
      backdrop-filter: blur(10px);
    }
  }
`

export const topSpacer = styled.div`
  flex: 45 0 auto;
`

export const content = styled.div`
  flex: 0 0 auto;
  border-radius: 16px;
  padding: 16px;
  background: ${color.container.background};
  animation-name: modal-content-fade-in;
  animation-easing-function: ease-out;
  animation-duration: var(--self-animation-duration);
  animation-fill-mode: both;

  @media (width < ${breakpoint}) {
    border-radius: 16px 16px 0 0;
    animation-name: modal-content-slide-in;
  }

  @keyframes modal-content-slide-in {
    from { transform: translate(0, calc(100% + 20px)); }
    to { transform: translate(0, 0); }
  }

  @keyframes modal-content-fade-in {
    from { opacity: 0; }
    to { opacity: 1; }
  }
`

export const bottomSpacer = styled.div`
  flex: 55 0 auto;

  @media (width < ${breakpoint}) {
    flex: 0 0 0;
  }
`

export const close = styled.div`
  color: ${color.icon.default};

  button {
    margin: 0;
    padding: 6px;
    background: none;
    border: none;
    cursor: pointer;
  }

  button:hover {
    background: color-mix(
      in srgb, ${color.button.background} 5% , ${color.white});
    border-radius: 6px;
  }

  button:disabled {
    color: ${color.icon.disabled};
    background: none;
    cursor: default;
  }

  --leo-icon-size: 24px;
`
