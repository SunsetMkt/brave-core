// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import styled from 'styled-components'
import { getLocale } from '$web-common/locale'

const Box = styled.div`
  display: flex;
  justify-content: center;
  flex-direction: column;
  align-items: center;
  gap: 20px;
  width: 100%;
`

const Form = styled.form`
  --bg-color: rgba(255, 255, 255, 0.7);
  --box-shadow: 0px 2px 70px rgba(0, 0, 0, 0.3);

  display: grid;
  grid-template-columns: 1fr 50px;
  align-items: center;
  width: 100%;
  height: 56px;
  font-family: ${p => p.theme.fontFamily.heading};
  color: #6B7084;
  font-size: 16px;
  font-weight: 400;
  background: var(--bg-color);
  backdrop-filter: blur(55px);
  border-radius: 16px;
  transition: box-shadow 0.3s ease-in-out;
  overflow: hidden;

  &:focus-within,
  &:hover {
    box-shadow: var(--box-shadow);
  }

  input[type="text"] {
    width: 100%;
    height: 36px;
    border: 0;
    background-color: transparent;
    padding: 5px 16px;

    &:focus {
      outline: 0;
    }
  }
`

const IconButton = styled.button`
  background: transparent;
  padding: 0;
  margin: 0;
  border: 0;
  width: 100%;
  height: 100%;
  cursor: pointer;

  &:hover {
    background: linear-gradient(304.74deg, #6F4CD2 15.81%, #BF14A2 63.17%, #F73A1C 100%);

    path {
      fill: white;
    }
  }
`

function BraveSearchLogo () {
  return (
    <svg width="256" height="78" fill="none" xmlns="http://www.w3.org/2000/svg">
      <path fillRule="evenodd" clipRule="evenodd" d="M85.5479 42.2678V15.4844H88.1173C90.2107 15.4844 91.9078 17.1765 91.9078 19.2639V31.1726C96.0256 27.5093 99.5274 26.0428 104.195 25.9487C113.146 25.7661 120.916 32.3956 121.654 41.2939C122.536 51.9243 114.783 59.9261 104.683 59.9261C93.5949 59.9261 85.5479 53.0698 85.5479 42.2678ZM91.8023 44.3707C92.4295 49.9044 97.7294 54.4753 103.318 54.5639C110.599 54.6746 115.56 49.9432 115.56 42.943C115.56 35.9427 110.71 31.322 103.634 31.322C96.07 31.3054 90.9422 36.7839 91.8023 44.3707Z" fill="white"/>
      <path fillRule="evenodd" clipRule="evenodd" d="M132.265 26.6183V31.3884C136.266 26.9614 138.636 25.7716 143.32 25.7716C144.682 25.7731 146.042 25.8822 147.388 26.0981V32.4343C145.952 32.0408 144.47 31.8435 142.981 31.8477C139.59 31.8477 136.743 32.9544 134.657 35.0462C132.825 36.8779 132.281 38.3111 132.281 41.1887V58.8304H125.688V26.6183H132.265Z" fill="white"/>
      <path fillRule="evenodd" clipRule="evenodd" d="M148.953 37.2708C149.291 34.1331 149.902 32.4343 151.256 30.8018C153.97 27.4815 158.853 25.7716 165.768 25.7716C171.262 25.7716 175.264 26.6238 178.044 28.45C180.353 29.9496 181.302 32.1742 181.302 36.0921V50.3969C181.302 53.5345 182.117 54.6413 184.354 54.5804C184.854 54.5628 185.352 54.5185 185.847 54.4476V58.7584C184.735 59.1373 183.564 59.3135 182.389 59.2786C178.255 59.2786 176.357 58.039 175.069 54.4421C171.001 58.1663 166.795 59.7324 160.762 59.7324C152.693 59.7324 147.743 56.0745 147.743 50.1257C147.708 46.7334 149.709 43.6485 152.826 42.2899C155.268 41.244 156.761 40.9175 163.743 40.1982C169.708 39.6116 170.73 39.4788 172.422 38.9531C174.254 38.3665 175.069 37.387 175.069 35.7545C175.069 32.2904 172.156 30.7243 166.051 30.7243C160.28 30.7243 157.305 31.8643 156.112 34.7751C155.521 36.2635 154.082 37.2447 152.477 37.2542L148.953 37.2708ZM175.036 42.7602C170.853 43.9733 166.558 44.7613 162.216 45.1121C156.317 45.6987 154.486 46.811 154.486 49.7494C154.486 53.0143 157.199 54.7298 162.555 54.7298C166.961 54.7298 170.286 53.623 172.661 51.4649C174.559 49.6996 175.036 48.46 175.036 45.3777V42.7602Z" fill="white"/>
      <path fillRule="evenodd" clipRule="evenodd" d="M201.763 58.8248H200.065C198.569 58.8342 197.2 57.9862 196.547 56.6445L182.323 26.6183H186.274C188.577 26.5999 190.673 27.9391 191.618 30.0326L201.108 51.6143L210.915 29.9496C211.874 27.8891 213.953 26.5779 216.231 26.5961H219.822L205.265 56.6777C204.604 58.0011 203.246 58.8341 201.763 58.8248Z" fill="white"/>
      <path fillRule="evenodd" clipRule="evenodd" d="M224.278 44.5864C224.955 50.7953 229.828 54.6468 237.092 54.6468C241.216 54.6468 244.307 53.4238 246.221 50.9834C247.338 49.584 249.034 48.769 250.828 48.7699H254.651C251.322 56.0856 245.361 59.6825 236.476 59.6825C225.377 59.6825 217.896 52.9535 217.896 42.8931C217.896 32.8327 225.56 25.7771 236.615 25.7771C244.612 25.7771 251.044 29.3685 253.636 35.3837C254.79 38.1506 255.262 40.6076 255.262 44.5919L224.278 44.5864ZM248.552 39.606C247.059 33.9228 242.653 30.7188 236.548 30.7188C230.444 30.7188 226.037 33.9228 224.478 39.606H248.552Z" fill="white"/>
      <path fillRule="evenodd" clipRule="evenodd" d="M65.1504 18.6727L66.9789 14.1919C66.9789 14.1919 64.6517 11.7025 61.8259 8.88121C59.0001 6.05994 53.0159 7.71951 53.0159 7.71951L46.2007 0H34.2324H22.2642L15.4489 7.71951C15.4489 7.71951 9.46481 6.05994 6.63898 8.88121C3.81314 11.7025 1.48598 14.1919 1.48598 14.1919L3.31446 18.6727L0.987305 25.311C0.987305 25.311 7.83165 51.1929 8.63369 54.3536C10.2128 60.577 11.2933 62.9833 15.7814 66.1365C20.2695 69.2897 28.4145 74.7663 29.7443 75.5961C31.0742 76.4259 32.7364 77.8393 34.2324 77.8393C35.7285 77.8393 37.3907 76.4259 38.7205 75.5961C40.0503 74.7663 48.1954 69.2897 52.6835 66.1365C57.1716 62.9833 58.2521 60.577 59.8312 54.3536C60.6331 51.1929 67.4776 25.311 67.4776 25.311L65.1504 18.6727Z" fill="url(#paint0_linear_1095_11330)"/>
      <path fillRule="evenodd" clipRule="evenodd" d="M42.71 14.0259C43.7073 14.0259 51.1044 12.6153 51.1044 12.6153C51.1044 12.6153 59.8704 23.1951 59.8704 25.4562C59.8704 27.3258 59.1166 28.0575 58.2288 28.9193C58.0429 29.0998 57.851 29.2861 57.659 29.4897L51.0861 36.458C51.0209 36.5271 50.9484 36.5999 50.8716 36.677C50.2156 37.3356 49.2494 38.3054 49.9311 39.9161C49.9767 40.0238 50.0236 40.1332 50.0712 40.2443C50.8186 41.9894 51.7412 44.1436 50.5668 46.3267C49.3174 48.6488 47.1773 50.1987 45.8059 49.9424C44.4346 49.686 41.2139 48.0057 40.0296 47.2381C38.8452 46.4706 35.0915 43.3798 35.0915 42.1972C35.0915 41.2109 37.7911 39.5701 39.1027 38.7728C39.3636 38.6143 39.5696 38.4891 39.6885 38.409C39.8239 38.318 40.0503 38.1775 40.329 38.0046C41.5262 37.262 43.6879 35.9212 43.7422 35.3267C43.8091 34.5937 43.7836 34.3788 42.8187 32.5678C42.6135 32.1827 42.3734 31.7703 42.1252 31.344C41.2064 29.7656 40.1775 27.9982 40.4053 26.7321C40.6624 25.3029 42.9054 24.4835 44.8053 23.7894C45.0428 23.7027 45.2749 23.6179 45.4971 23.5341C46.0516 23.3251 46.7483 23.0645 47.4762 22.7923C49.3731 22.0829 51.4807 21.2947 51.8283 21.1347C52.3095 20.9131 52.1852 20.7022 50.7279 20.5643C50.5351 20.546 50.2954 20.5206 50.0203 20.4914C48.2163 20.3 44.8892 19.947 43.2716 20.3972C42.9535 20.4857 42.5969 20.5821 42.2229 20.6832C40.4056 21.1746 38.1785 21.7767 37.9646 22.1238C37.9271 22.1845 37.8903 22.2367 37.8556 22.286C37.6509 22.5765 37.5175 22.7659 37.744 24.0003C37.8114 24.3679 37.9501 25.0909 38.1215 25.9849C38.6235 28.6025 39.4065 32.6855 39.5051 33.6027C39.519 33.7311 39.5342 33.855 39.5488 33.9742C39.6744 34.9975 39.7579 35.6785 38.5676 35.9502C38.4685 35.9728 38.3644 35.9967 38.2562 36.0215C36.913 36.3292 34.9439 36.7803 34.2325 36.7803C33.5207 36.7803 31.5501 36.3288 30.207 36.0211C30.0994 35.9964 29.9959 35.9727 29.8973 35.9502C28.7068 35.6785 28.7904 34.9975 28.916 33.9741C28.9306 33.855 28.9458 33.7311 28.9596 33.6027C29.0585 32.6842 29.8435 28.591 30.3455 25.9739C30.5159 25.085 30.6538 24.3664 30.7209 24.0003C30.9473 22.766 30.8139 22.5766 30.6093 22.2861C30.5746 22.2368 30.5378 22.1846 30.5004 22.1238C30.2864 21.7767 28.0595 21.1746 26.2422 20.6833C25.8681 20.5822 25.5114 20.4857 25.1931 20.3972C23.5757 19.9471 20.2489 20.3 18.4448 20.4914C18.1696 20.5206 17.9298 20.546 17.7369 20.5643C16.2798 20.7022 16.1554 20.9131 16.6365 21.1347C16.984 21.2946 19.0906 22.0824 20.9872 22.7917C21.7155 23.0641 22.413 23.3249 22.9678 23.5341C23.1901 23.6179 23.4223 23.7028 23.6599 23.7896C25.5597 24.4836 27.8026 25.303 28.0597 26.7321C28.2874 27.998 27.2587 29.765 26.34 31.3433C26.0918 31.7698 25.8515 32.1825 25.6462 32.5678C24.6813 34.3788 24.6557 34.5937 24.7227 35.3267C24.7769 35.9211 26.9378 37.2615 28.1351 38.0042C28.4141 38.1773 28.6408 38.3179 28.7763 38.409C28.8951 38.489 29.1009 38.6141 29.3615 38.7725C30.673 39.5696 33.3732 41.2108 33.3732 42.1972C33.3732 43.3798 29.6197 46.4706 28.4353 47.2381C27.251 48.0057 24.0304 49.686 22.659 49.9424C21.2876 50.1987 19.1475 48.6488 17.8981 46.3267C16.7238 44.1438 17.6462 41.9897 18.3935 40.2447C18.4411 40.1335 18.488 40.0239 18.5336 39.9161C19.2154 38.3052 18.2491 37.3354 17.5929 36.6768C17.5162 36.5998 17.4438 36.527 17.3787 36.458L10.8058 29.4897C10.6138 29.2861 10.422 29.0999 10.2361 28.9194C9.34827 28.0576 8.59448 27.3258 8.59448 25.4562C8.59448 23.1951 17.3606 12.6153 17.3606 12.6153C17.3606 12.6153 24.7576 14.0259 25.755 14.0259C26.5508 14.0259 28.0875 13.4975 29.6895 12.9468C30.0951 12.8073 30.5049 12.6664 30.9079 12.5323C32.9027 11.8685 34.2325 11.8636 34.2325 11.8636C34.2325 11.8636 35.5623 11.8685 37.557 12.5323C37.96 12.6664 38.3698 12.8073 38.7754 12.9468C40.3774 13.4975 41.9141 14.0259 42.71 14.0259ZM41.4403 51.4478C43.004 52.2523 44.1133 52.823 44.5328 53.085C45.0753 53.4243 44.7444 54.0637 44.2502 54.4125C43.7558 54.7614 37.1133 59.8968 36.4687 60.4643C36.3862 60.537 36.2987 60.6157 36.2076 60.6977C35.5864 61.2566 34.7941 61.9696 34.2324 61.9696C33.6705 61.9696 32.8777 61.2561 32.2565 60.697C32.1656 60.6152 32.0784 60.5368 31.9962 60.4643C31.3514 59.8968 24.709 54.7614 24.2147 54.4125C23.7203 54.0637 23.3895 53.4243 23.9321 53.085C24.3518 52.8228 25.4622 52.2516 27.0275 51.4463C27.4863 51.2103 27.9841 50.9541 28.5151 50.6798C30.8574 49.4697 33.7768 48.4407 34.2324 48.4407C34.6881 48.4407 37.6073 49.4697 39.9499 50.6798C40.482 50.9547 40.9807 51.2113 41.4403 51.4478Z" fill="white"/>
      <path fillRule="evenodd" clipRule="evenodd" d="M53.0159 7.71951L46.2006 0H34.2324H22.2641L15.4489 7.71951C15.4489 7.71951 9.46475 6.05994 6.63892 8.88121C6.63892 8.88121 14.6177 8.16212 17.3605 12.6153C17.3605 12.6153 24.7575 14.0259 25.7549 14.0259C26.7522 14.0259 28.9132 13.1961 30.9079 12.5323C32.9026 11.8684 34.2324 11.8636 34.2324 11.8636C34.2324 11.8636 35.5622 11.8684 37.5569 12.5323C39.5516 13.1961 41.7125 14.0259 42.7099 14.0259C43.7072 14.0259 51.1043 12.6153 51.1043 12.6153C53.847 8.16212 61.8258 8.88121 61.8258 8.88121C59 6.05994 53.0159 7.71951 53.0159 7.71951Z" fill="url(#paint1_linear_1095_11330)"/>
      <defs>
        <linearGradient id="paint0_linear_1095_11330" x1="0.987305" y1="78.3885" x2="67.4776" y2="78.3885" gradientUnits="userSpaceOnUse">
          <stop stopColor="#FF5500"/>
          <stop offset="0.409877" stopColor="#FF5500"/>
          <stop offset="0.581981" stopColor="#FF2000"/>
          <stop offset="1" stopColor="#FF2000"/>
        </linearGradient>
        <linearGradient id="paint1_linear_1095_11330" x1="6.63892" y1="14.1248" x2="61.8258" y2="14.1248" gradientUnits="userSpaceOnUse">
          <stop stopColor="#FF5500"/>
          <stop offset="0.409877" stopColor="#FF5500"/>
          <stop offset="0.581981" stopColor="#FF2000"/>
          <stop offset="1" stopColor="#FF2000"/>
        </linearGradient>
      </defs>
    </svg>
  )
}

interface Props {
  onSubmit: (value: string, openNewTab: boolean) => unknown
}

function Search (props: Props) {
  const [value, setValue] = React.useState('')
  const inputRef = React.useRef<HTMLInputElement>(null)

  const onInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setValue(e.currentTarget.value)
  }

  const handleFormBoxClick = () => {
    inputRef.current && inputRef.current.focus()
  }

  const handleSubmit = (e: React.ChangeEvent<HTMLFormElement>) => {
    e.preventDefault()
    props.onSubmit(value, false)
  }

  const handleKeyDown = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (value === '') return

    if ((e.metaKey || e.ctrlKey) && (e.key === 'Enter')) {
      props.onSubmit(value, true)
    }
  }

  return (
    <Box>
      <BraveSearchLogo />
      <Form onSubmit={handleSubmit} onClick={handleFormBoxClick} role="search" aria-label="Brave">
        <input ref={inputRef} onChange={onInputChange} onKeyDown={handleKeyDown} type="text" placeholder={getLocale('searchPromotionSearchBoxPlaceholderLabel')} value={value} autoCapitalize="off" autoComplete="off" autoCorrect="off" spellCheck="false" aria-label="Search" title="Search" aria-autocomplete="none" aria-haspopup="false" maxLength={2048} autoFocus />
        <IconButton data-test-id="submit_button" aria-label="Submit">
          <svg width="20" height="20" fill="none" xmlns="http://www.w3.org/2000/svg"><path fillRule="evenodd" clipRule="evenodd" d="M8 16a8 8 0 1 1 5.965-2.67l5.775 5.28a.8.8 0 1 1-1.08 1.18l-5.88-5.375A7.965 7.965 0 0 1 8 16Zm4.374-3.328a.802.802 0 0 0-.201.18 6.4 6.4 0 1 1 .202-.181Z" fill="url(#search_icon_gr)"/><defs><linearGradient id="search_icon_gr" x1="20" y1="20" x2="-2.294" y2="3.834" gradientUnits="userSpaceOnUse"><stop stopColor="#BF14A2"/><stop offset="1" stopColor="#F73A1C"/></linearGradient></defs></svg>
        </IconButton>
      </Form>
    </Box>
  )
}

export default Search
