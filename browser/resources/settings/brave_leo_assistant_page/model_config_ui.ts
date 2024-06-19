/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import 'chrome://resources/cr_elements/cr_button/cr_button.js'
import 'chrome://resources/cr_elements/icons.html.js'

import { PrefsMixin } from '/shared/settings/prefs/prefs_mixin.js'
import { I18nMixin } from 'chrome://resources/cr_elements/i18n_mixin.js'
import { PolymerElement } from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js'
import * as mojom from './brave_leo_assistant_browser_proxy.js'
import { BaseMixin } from '../base_mixin.js'
import { getTemplate } from './model_config_ui.html.js'

const ModelConfigUIBase = PrefsMixin(I18nMixin(BaseMixin(PolymerElement)))

class ModelConfigUI extends ModelConfigUIBase {
  static get is() {
    return 'model-config-ui'
  }

  static get template() {
    return getTemplate()
  }

  static get properties() {
    return {
      label: {
        type: String
      },
      modelRequestName: {
        type: String
      },
      endpointUrl: {
        type: String
      },
      apiKey: {
        type: String,
        value: ''
      },
      isUrlInvalid: {
        type: Boolean,
        value: false
      },
      modelItem: {
        type: Object,
        value: null,
        notify: true,
        observer: 'onModelItemChange_'
      },
      isEditing_: {
        type: Boolean,
        value: false,
        readOnly: true,
        computed: 'computeIsEditing_(modelItem)'
      },
      buttonLabel_: {
        type: String,
        computed: 'computeButtonLabel_(isEditing_)'
      }
    }
  }

  label: string
  modelRequestName: string
  endpointUrl: string
  apiKey: string
  modelItem: mojom.Model | null
  isEditing_: boolean
  isUrlInvalid: boolean

  override ready() {
    super.ready()
  }

  handleClick_() {
    if (!this.saveEnabled_()) {
      return
    }

    const mojomUrl = { url: '' }
    mojomUrl.url = this.endpointUrl

    const modelConfig: mojom.Model = {
      options: {
        customModelOptions: {
          modelRequestName: this.modelRequestName,
          endpoint: mojomUrl,
          apiKey: this.apiKey
        }
      },
      // Adding random string to make sure the key is unique
      key: `custom:${
        new URL(this.endpointUrl).host
      }:${this.modelRequestName.toLowerCase()}:${crypto
        .randomUUID()
        .slice(0, 8)}`,
      displayName: this.label
    }

    this.fire('save', { modelConfig })
  }

  handleCloseClick_() {
    this.fire('close')
  }

  onModelLabelChange_(e: any) {
    this.label = e.target.value
  }

  onModelRequestNameChange_(e: any) {
    this.modelRequestName = e.target.value
  }

  onModelServerEndpointChange_(e: any) {
    this.endpointUrl = e.target.value
  }

  onModelApiKeyChange_(e: any) {
    this.apiKey = e.target.value
  }

  private saveEnabled_() {
    // Make sure all required fields are filled
    return this.label && this.modelRequestName && this.endpointUrl
  }

  private onModelItemChange_(newValue: mojom.Model | null) {
    if (newValue && newValue.options.customModelOptions) {
      this.label = newValue.displayName
      this.modelRequestName =
        newValue.options.customModelOptions.modelRequestName
      this.endpointUrl = newValue.options.customModelOptions.endpoint.url
      this.apiKey = newValue.options.customModelOptions.apiKey
    }
  }

  private computeIsEditing_(modelItem: mojom.Model | null) {
    return !!modelItem
  }

  private computeButtonLabel_(isEditing: boolean) {
    return isEditing ? 'Save' : 'Add model'
  }
}

customElements.define(ModelConfigUI.is, ModelConfigUI)
