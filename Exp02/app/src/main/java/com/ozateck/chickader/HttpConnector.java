package com.ozateck.chickader;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import okhttp3.Call;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

public class HttpConnector implements HttpTask.HttpEventListener {

	public static final String TAG = "HttpConnector";

	HttpConnector() {
		CustomLog.d(TAG, "HttpConnector");
	}

	void connect(final String url) {
		CustomLog.d(TAG, "connect()");
		// HttpTask
		HttpTask task = new HttpTask(url, this);
		// Execute
		ExecutorService eService = Executors.newSingleThreadExecutor();
		eService.execute(task);
	}

	@Override
	public void onSuccess(final String result) {
		CustomLog.d(TAG, "onSuccess()");
		MainActivity.nativeOnHttpSuccess(result);// JNI
	}

	@Override
	public void onError(final String err) {
		CustomLog.d(TAG, "onError()");
		MainActivity.nativeOnHttpError(err);// JNI
	}
}

class HttpTask implements Runnable {

	public static final String TAG = "HttpTask";
	private String url = null;
	private HttpEventListener listener = null;

	HttpTask(final String url, HttpEventListener listener) {
		CustomLog.d(TAG, "HttpTask");
		this.url = url;
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

		void onSuccess(final String result);

		void onError(final String err);
	}
}