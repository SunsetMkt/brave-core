/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import * as React from 'react'

import Button from '@brave/leo/react/button'
import { useLocaleContext } from '../../lib/locale_strings'
import { Modal, ModalCloseButton } from '../modal'
import { CountrySelect } from './country_select'

import selectCountryGraphic from '../../assets/select_country.svg'

import * as style from './country_select_modal.style'

interface Props {
  loading: boolean
  countries: string[]
  defaultCountry: string
  onClose: () => void
  onCountrySelected: (countryCode: string) => void
}

export function CountrySelectModal (props: Props) {
  const { getString } = useLocaleContext()
  const [countryCode, setCountryCode] = React.useState('')

  function onContinueClick () {
    if (countryCode) {
      props.onCountrySelected(countryCode)
    }
  }

  return (
    <Modal>
      <style.root>
        <style.header>
          <ModalCloseButton
            isDisabled={props.loading}
            onClick={props.onClose}
          />
        </style.header>
        <style.graphic>
          <img src={selectCountryGraphic} />
        </style.graphic>
        <style.title>
          {getString('countrySelectTitle')}
        </style.title>
        <style.text>
          {getString('countrySelectText')}
        </style.text>
        <style.selector>
          <CountrySelect
            countries={props.countries}
            defaultCountry={props.defaultCountry}
            placeholderText={getString('countrySelectPlaceholder')}
            value={countryCode}
            onChange={setCountryCode}
          />
        </style.selector>
        <style.actions>
          <Button
            isDisabled={!countryCode}
            isLoading={props.loading}
            onClick={onContinueClick}
          >
            {getString('continueButtonLabel')}
          </Button>
          <Button
            kind='plain'
            isDisabled={props.loading}
            onClick={props.onClose}
          >
            {getString('cancelButtonLabel')}
          </Button>
        </style.actions>
      </style.root>
    </Modal>
  )
}
