/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import Icon from '@brave/leo/react/icon'

import * as style from './modal.style'

interface ModalProps {
  onBackdropClick?: () => void
  children: React.ReactNode
}

// When switching between modals, we don't want the fade-in or slide-in
// animations to appear. When a modal is closed, we add a class to the document
// body for a short period of time which is used to disable animations in CSS.
let animationCoolDownTimeout = 0
const animationCoolDownDelay = 500

function startAnimationCoolDown () {
  const cssClass = 'modal-skip-animations'
  if (animationCoolDownTimeout) {
    clearTimeout(animationCoolDownTimeout)
  }
  document.body.classList.add(cssClass)
  animationCoolDownTimeout = setTimeout(() => {
    document.body.classList.remove(cssClass)
    animationCoolDownTimeout = 0
  }, animationCoolDownDelay) as any // `any` to work around `Timeout` mis-typing
}

export function Modal(props: ModalProps) {
  // Attach a ResizeObserver for the modal content container. When the content
  // size changes, set a CSS variable "--modal-content-size" on the document
  // body. This is primarily used by browser "bubbles" in order to automatically
  // adjust the height of the bubble when a modal is displayed.
  const resizeObserver = React.useMemo(() => {
    return new ResizeObserver((entries) => {
      for (const entry of entries) {
        if (entry.borderBoxSize.length > 0) {
          document.body.style.setProperty(
            '--modal-content-block-size',
            `${entry.borderBoxSize[0].blockSize}px`)
        }
      }
    })
  }, [])

  function onMountUnmount (elem: HTMLElement | null) {
    if (elem) {
      resizeObserver.observe(elem)
    } else {
      resizeObserver.disconnect()
      document.body.style.removeProperty('--modal-content-block-size')
      startAnimationCoolDown()
    }
  }

  function stopClickPropagation (evt: React.MouseEvent) {
    evt.stopPropagation()
  }

  return (
    <style.root onClick={props.onBackdropClick}>
      <style.topSpacer />
      <style.content ref={onMountUnmount} onClick={stopClickPropagation}>
        {props.children}
      </style.content>
      <style.bottomSpacer />
    </style.root>
  )
}

interface ModalCloseButtonProps {
  isDisabled?: boolean
  onClick: () => void
}

export function ModalCloseButton (props: ModalCloseButtonProps) {
  return (
    <style.close>
      <button
        disabled={props.isDisabled}
        onClick={props.onClick}
      >
        <Icon name='close' />
      </button>
    </style.close>
  )
}
