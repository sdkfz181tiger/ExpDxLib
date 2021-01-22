package com.ozateck.chickader;

import android.app.NativeActivity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;

import java.io.File;

public class MainActivity extends NativeActivity {

	private static final String TAG = "MainActivity";
	private static Context ctx = null;
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
		setContentView(R.layout.activity_main);
		MainActivity.nativeOnCreate();// Native
		// Context, Version, filePath
		ctx = this.getApplicationContext();
		versionCode = getVersionCode(ctx, ctx.getPackageManager());
		versionName = getVersionName(ctx, ctx.getPackageManager());
		filePath = ctx.getFilesDir().getPath() + File.separator;
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

	public static boolean getDebugFlg() { return debugFlg; }

	public static void connectServer(final String url, final String fileName) {
		if (ctx == null) return;
		final HttpConnector hCon = new HttpConnector(ctx);
		hCon.connect(url, fileName);
	}
}