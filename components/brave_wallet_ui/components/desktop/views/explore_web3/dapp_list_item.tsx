// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// types
import { BraveWallet } from '../../../../constants/types'

// styles
import { Column, Row, Text } from '../../../shared/style'
import {
  TextWithOverflowEllipsis //
} from '../../../../page/screens/send/shared.styles'

export const DappListItem = React.forwardRef<
  HTMLDivElement,
  {
    dapp: BraveWallet.Dapp
    ref: React.Ref<HTMLDivElement>
    onClick?: (dappId: number) => void
  }
>(({ dapp, onClick }, ref) => {
  return (
    <Row
      ref={ref}
      gap={'8px'}
      padding={'12px 8px'}
      width='100%'
      justifyContent='flex-start'
      onClick={
        onClick
          ? function () {
              onClick(dapp.id)
            }
          : undefined
      }
    >
      <Column>
        <img
          src={`chrome://image?${dapp.logo}`}
          height={40}
          width={40}
        />
      </Column>
      <Column
        alignItems='flex-start'
        justifyContent='flex-start'
      >
        <Text
          textAlign='left'
          isBold
          textSize='14px'
        >
          {dapp.name}
        </Text>

        <TextWithOverflowEllipsis
          textSize='12px'
          textAlign='left'
          textColor='tertiary'
          maxLines={1}
        >
          {dapp.description}
        </TextWithOverflowEllipsis>
      </Column>
    </Row>
  )
})
