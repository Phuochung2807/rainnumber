/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import org.json.JSONException;
import org.json.JSONObject;

import com.easyndk.classes.AndroidNDKHelper;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import newbie.games.rainnumber.R;
import 	android.view.Gravity;
import com.google.android.gms.ads.InterstitialAd;

public class AppActivity extends Cocos2dxActivity {
	private FrameLayout rootView;
	AdView adView;
	LinearLayout adsLayout;
	InterstitialAd mInterstitialAd;
	Boolean isLoadAds;

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AndroidNDKHelper.SetNDKReceiver(this);
		setVolumeControlStream(android.media.AudioManager.STREAM_MUSIC);
		isLoadAds = false;
	}

	public void loadAd(JSONObject parameters) {
		if (parameters != null) {
			try {
				String ad_mob_id = parameters.getString("ad_mob_id");
				adsLayout = new LinearLayout(this);
LinearLayout.LayoutParams adParams = new LinearLayout.LayoutParams(
    		LinearLayout.LayoutParams.WRAP_CONTENT,
    		LinearLayout.LayoutParams.WRAP_CONTENT);
adParams.gravity = Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL;
				adView = new AdView(this);
				adView.setAdSize(AdSize.SMART_BANNER);
				adView.setAdUnitId(ad_mob_id);

				String ad_mob_inter_id = parameters.getString("ad_mob_inter_id");
				mInterstitialAd = new InterstitialAd(this);
        		mInterstitialAd.setAdUnitId(ad_mob_inter_id);

				AdRequest adRequest = new AdRequest.Builder()
						.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
						.addTestDevice("FD6E971B2766B8C79E91E83179768179")
						.addTestDevice("2D3F66CF1DC1C7EEE76C387F2FDD48F1")
						.addTestDevice("35C0DB7AB9AB50EB4D7FD36C73390B60")
						.build();

				adView.loadAd(adRequest);
				mInterstitialAd.loadAd(adRequest);
				adsLayout.addView(adView, adParams);
				this.GetRootView().addView(adsLayout);

			} catch (JSONException e) {
				e.printStackTrace();
			}
		}
	}

	private FrameLayout GetRootView() {
		if (this.rootView == null) {
			this.rootView = (FrameLayout) this.getWindow().getDecorView()
					.findViewById(android.R.id.content);
		}

		return this.rootView;
	}

	public void hideAd(JSONObject parameters) {
		adsLayout.setVisibility(View.INVISIBLE);
		if (isLoadAds)
		{
			AdRequest adRequest = new AdRequest.Builder()
						.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
						.addTestDevice("FD6E971B2766B8C79E91E83179768179")
						.addTestDevice("2D3F66CF1DC1C7EEE76C387F2FDD48F1")
						.addTestDevice("35C0DB7AB9AB50EB4D7FD36C73390B60")
						.build();

			//adView.loadAd(adRequest);
			mInterstitialAd.loadAd(adRequest);
			isLoadAds = false;
		}
	}

	public void showAd(JSONObject parameters) {
		adsLayout.setVisibility(View.VISIBLE);
	}

	public void showAdInter(JSONObject parameters)
	{
		if (mInterstitialAd.isLoaded()) {
            mInterstitialAd.show();
            isLoadAds = true;
        }
	}
}
