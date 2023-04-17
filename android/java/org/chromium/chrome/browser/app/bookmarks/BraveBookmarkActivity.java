/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.app.bookmarks;

import android.content.Intent;
import android.os.Bundle;

import org.chromium.chrome.browser.bookmarks.BookmarkManager;
import org.chromium.chrome.browser.bookmarks.BraveBookmarkManager;
import org.chromium.ui.base.ActivityWindowAndroid;
import org.chromium.ui.base.IntentRequestTracker;

public class BraveBookmarkActivity extends BookmarkActivity {
    // Overridden Chromium's BookmarkActivity.mBookmarkManager
    private BookmarkManager mBookmarkManager;
    private ActivityWindowAndroid mWindowAndroid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        IntentRequestTracker intentRequestTracker = IntentRequestTracker.createFromActivity(this);
        mWindowAndroid = new ActivityWindowAndroid(this, true, intentRequestTracker);
        mWindowAndroid.getIntentRequestTracker().restoreInstanceState(savedInstanceState);
        assert mBookmarkManager != null;
        if (mBookmarkManager instanceof BraveBookmarkManager) {
            ((BraveBookmarkManager) mBookmarkManager).setWindow(mWindowAndroid);
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);

        mWindowAndroid.getIntentRequestTracker().saveInstanceState(outState);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        mWindowAndroid.getIntentRequestTracker().onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onRequestPermissionsResult(
            int requestCode, String[] permissions, int[] grantResults) {
        if (mWindowAndroid.handlePermissionResult(requestCode, permissions, grantResults)) return;
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }
}
