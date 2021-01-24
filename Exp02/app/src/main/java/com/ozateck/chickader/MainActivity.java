package com.ozateck.chickader;

import android.app.NativeActivity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.Gravity;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

import java.io.File;

public class MainActivity extends NativeActivity {

	private static final String TAG = "MainActivity";
	private static NativeActivity activity = null;
	private static String versionCode = "";
	private static String versionName = "";
	private static String filePath = "";
	private static boolean debugFlg = false;

	// Used to load the 'native-lib' library on application startup.
	static {
		System.loadLibrary("native-lib");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		MainActivity.nativeOnCreate();// Native
		// Activity, Version, filePath
		activity = this;
		versionCode = getVersionCode(this, this.getPackageManager());
		versionName = getVersionName(this, this.getPackageManager());
		filePath = this.getFilesDir().getPath() + File.separator;
		debugFlg = BuildConfig.DEBUG;
	}

	@Override
	protected void onStart() {
		super.onStart();
		MainActivity.nativeOnStart();// Native
	}

	@Override
	protected void onResume() {
		super.onResume();
		MainActivity.nativeOnResume();// Native
	}

	@Override
	protected void onPause() {
		MainActivity.nativeOnPause();// Native
		super.onPause();
	}

	@Override
	protected void onStop() {
		MainActivity.nativeOnStop();// Native
		super.onStop();
	}

	@Override
	protected void onDestroy() {
		MainActivity.nativeOnDestroy();// Native
		super.onDestroy();
	}

	private String getVersionCode(final Context ctx, final PackageManager pm) {
		try {
			PackageInfo info = pm.getPackageInfo(ctx.getPackageName(), 0);
			return String.valueOf(info.getLongVersionCode());
		} catch (Exception e) {
			CustomLog.d(TAG, "E:" + e.toString());
		}
		return "0";
	}

	private String getVersionName(final Context ctx, final PackageManager pm) {
		try {
			PackageInfo info = pm.getPackageInfo(ctx.getPackageName(), 0);
			return info.versionName;
		} catch (Exception e) {
			CustomLog.d(TAG, "E:" + e.toString());
		}
		return "0.0.0";
	}

	//==========
	// JNI(Java -> C++)
	public static native void nativeOnCreate();

	public static native void nativeOnStart();

	public static native void nativeOnResume();

	public static native void nativeOnPause();

	public static native void nativeOnStop();

	public static native void nativeOnDestroy();

	public static native void nativeOnHttpSuccess(final String fileName);

	public static native void nativeOnHttpProgress(final String fileName);

	public static native void nativeOnHttpError(final String fileName, final String err);

	//==========
	// JNI(C++ -> Java)
	public static String getVersionCode() {
		return versionCode;
	}

	public static String getVersionName() {
		return versionName;
	}

	public static String getFilePath() {
		return filePath;
	}

	public static boolean getDebugFlg() {
		return debugFlg;
	}

	public static void connectAdMob() {
		if (activity == null) return;

		// Banner
		activity.runOnUiThread(
				new Runnable() {
					@Override
					public void run() {
						showBanner();
					}
				}
		);
	}

	public static void connectGitHub(final String url, final String fileName) {
		if (activity == null) return;
		final HttpConnector hCon = new HttpConnector(activity);
		hCon.connect(url, fileName);
	}

	public static void showBanner() {
		if (activity == null) return;

		// Banner
		AdView mBanner = new AdView(activity);
		mBanner.setLayoutParams(new FrameLayout.LayoutParams(
				FrameLayout.LayoutParams.WRAP_CONTENT,
				FrameLayout.LayoutParams.WRAP_CONTENT));
		mBanner.setAdSize(AdSize.SMART_BANNER);
		mBanner.setAdUnitId(activity.getResources().getString(R.string.admob_ad_unit_id_banner));
		mBanner.setAdListener(new AdListener() {
			@Override
			public void onAdLoaded() {
				CustomLog.d(TAG, "Banner:onAdLoaded()");
				// FrameLayout
				FrameLayout fLayout = new FrameLayout(activity);
				fLayout.setLayoutParams(new LinearLayout.LayoutParams(
						LinearLayout.LayoutParams.WRAP_CONTENT,
						LinearLayout.LayoutParams.WRAP_CONTENT
				));
				// PopupWindow
				PopupWindow pWindow = new PopupWindow(activity);
				pWindow.setContentView(mBanner);
				pWindow.setWidth(mBanner.getAdSize().getWidthInPixels(activity));
				pWindow.setHeight(mBanner.getAdSize().getHeightInPixels(activity));
				pWindow.showAtLocation(fLayout, Gravity.TOP, 0, 0);
				pWindow.update();
			}

			@Override
			public void onAdFailedToLoad(int errorCode) {
				CustomLog.d(TAG, "Banner:onAdFailedToLoad():" + errorCode);
				switch (errorCode) {
					case AdRequest.ERROR_CODE_INTERNAL_ERROR:
						CustomLog.d(TAG, "ERROR_CODE_INTERNAL_ERROR");
						break;
					case AdRequest.ERROR_CODE_INVALID_REQUEST:
						CustomLog.d(TAG, "ERROR_CODE_INVALID_REQUEST");
						break;
					case AdRequest.ERROR_CODE_NETWORK_ERROR:
						CustomLog.d(TAG, "ERROR_CODE_NETWORK_ERROR");
						break;
					case AdRequest.ERROR_CODE_NO_FILL:
						CustomLog.d(TAG, "ERROR_CODE_NO_FILL");
						break;
					default:
						break;
				}
			}
		});
		// Request
		AdRequest.Builder bannerBuilder = new AdRequest.Builder();
		bannerBuilder.addTestDevice(activity.getResources().getString(R.string.device_pixel2));
		AdRequest mRequest = bannerBuilder.build();
		mBanner.loadAd(mRequest);
	}
}