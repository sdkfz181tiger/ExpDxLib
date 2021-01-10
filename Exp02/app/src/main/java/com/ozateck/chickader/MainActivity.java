package com.ozateck.chickader;

import android.app.NativeActivity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.pm.PackageInfo;
import android.os.Bundle;

public class MainActivity extends NativeActivity{

	public static final String TAG = "MainActivity";
	public static String versionCode = "";
	public static String versionName = "";
	public static String filePath = "";

	// Used to load the 'native-lib' library on application startup.
	static{
		System.loadLibrary("native-lib");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		MainActivity.nativeOnCreate();// Native
		// Version
		final Context ctx = this.getApplicationContext();
		final PackageManager pm = ctx.getPackageManager();
		versionCode = getVersionCode(ctx, pm);
		versionName = getVersionName(ctx, pm);
		filePath = ctx.getFilesDir().getPath();
	}

	@Override
	protected void onStart(){
		super.onStart();
		MainActivity.nativeOnStart();// Native
	}

	@Override
	protected void onResume(){
		super.onResume();
		MainActivity.nativeOnResume();// Native
	}

	@Override
	protected void onPause(){
		MainActivity.nativeOnPause();// Native
		super.onPause();
	}

	@Override
	protected void onStop(){
		MainActivity.nativeOnStop();// Native
		super.onStop();
	}

	@Override
	protected void onDestroy(){
		MainActivity.nativeOnDestroy();// Native
		super.onDestroy();
	}

	private String getVersionCode(final Context ctx, final PackageManager pm){
		try{
			PackageInfo info = pm.getPackageInfo(ctx.getPackageName(), 0);
			return String.valueOf(info.versionCode);
		}catch(Exception e){
			CustomLog.d(TAG, "E:" + e.toString());
		}
		return "0";
	}

	private String getVersionName(final Context ctx, final PackageManager pm){
		try{
			PackageInfo info = pm.getPackageInfo(ctx.getPackageName(), 0);
			return info.versionName;
		}catch(Exception e){
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

	//==========
	// JNI(C++ -> Java)
	public static String getVersionCode(){
		return versionCode;
	}

	public static String getVersionName(){
		return versionName;
	}

	public static String getFilePath(){
		return filePath;
	}
}