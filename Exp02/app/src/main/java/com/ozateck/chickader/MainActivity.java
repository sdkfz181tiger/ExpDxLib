package com.ozateck.chickader;

import android.app.NativeActivity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import okhttp3.Call;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

public class MainActivity extends NativeActivity {

	public static final String TAG = "MainActivity";
	public static String versionCode = "";
	public static String versionName = "";
	public static String filePath = "";

	// Used to load the 'native-lib' library on application startup.
	static {
		System.loadLibrary("native-lib");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		MainActivity.nativeOnCreate();// Native
		// Version
		final Context ctx = this.getApplicationContext();
		final PackageManager pm = ctx.getPackageManager();
		versionCode = getVersionCode(ctx, pm);
		versionName = getVersionName(ctx, pm);
		filePath = ctx.getFilesDir().getPath();
		// Test
		HttpConnector hCon = new HttpConnector();
		hCon.connect("https://blog.goo.ne.jp/iwadas/index.rdf");
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

	public static native void nativeOnHttpSuccess();

	public static native void nativeOnHttpError();

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
}

class HttpConnector implements HttpTask.HttpEventListener {

	public static final String TAG = "HttpConnector";

	HttpConnector() {
		CustomLog.d(TAG, "HttpConnector");
	}

	void connect(final String url) {
		CustomLog.d(TAG, "connect()");
		// HttpTask
		HttpTask task = new HttpTask(url);
		task.addEventListener(this);
		// Execute
		ExecutorService eService = Executors.newSingleThreadExecutor();
		eService.execute(task);
	}

	@Override
	public void onSuccess(final String str) {
		CustomLog.d(TAG, "onSuccess():" + str);
		MainActivity.nativeOnHttpSuccess();// JNI
	}

	@Override
	public void onError(final String err) {
		CustomLog.d(TAG, "onError():" + err);
		MainActivity.nativeOnHttpError();// JNI
	}
}

class HttpTask implements Runnable {

	public static final String TAG = "HttpTask";
	private String url = null;
	private HttpEventListener listener = null;

	HttpTask(final String url) {
		CustomLog.d(TAG, "HttpTask");
		this.url = url;
	}

	public void addEventListener(HttpEventListener listener) {
		this.listener = listener;
	}

	@Override
	public void run() {
		CustomLog.d(TAG, "run()");
		OkHttpClient client = new OkHttpClient();
		Request request = new Request.Builder().url(url).build();
		Call call = client.newCall(request);
		try {
			Response response = call.execute();
			ResponseBody body = response.body();
			if (listener != null) listener.onSuccess(body.string());
		} catch (IOException e) {
			if (listener != null) listener.onError(e.toString());
		}
	}

	interface HttpEventListener {

		void onSuccess(final String str);

		void onError(final String err);
	}
}