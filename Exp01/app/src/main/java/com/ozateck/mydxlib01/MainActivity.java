package com.ozateck.mydxlib01;

import android.app.NativeActivity;
import android.os.Bundle;

public class MainActivity extends NativeActivity {

	// Used to load the 'native-lib' library on application startup.
	static {
		System.loadLibrary("native-lib");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		MainActivity.nativeOnCreate();// Native
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
		super.onPause();
		MainActivity.nativeOnPause();// Native
	}

	@Override
	protected void onStop() {
		super.onStop();
		MainActivity.nativeOnStop();// Native
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		MainActivity.nativeOnDestroy();// Native
	}

	//==========
	// JNI
	public static native void nativeOnCreate();

	public static native void nativeOnStart();

	public static native void nativeOnResume();

	public static native void nativeOnPause();

	public static native void nativeOnStop();

	public static native void nativeOnDestroy();
}