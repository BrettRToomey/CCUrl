#ifndef CURL_SHIM_H
#define CURL_SHIM_H 

#include <curl/curl.h>

#define CURL_TRUE 1
#define CURL_FALSE 0

extern inline CURLcode curl_setopt_bool(CURL *curl, CURLoption option, int value) {
	return curl_easy_setopt(curl, option, value == CURL_TRUE ? 1L : 0L);
}

extern inline CURLcode curl_setopt_int(CURL *curl, CURLoption option, long value) {
	return curl_easy_setopt(curl, option, value);
}

extern inline CURLcode curl_setopt_string(CURL *curl, CURLoption option, const char *value) {
	return curl_easy_setopt(curl, option, value);
}

extern inline CURLcode curl_setopt_writefunc(CURL *curl, void *user_struct, size_t (*write_cb)(char *ptr, size_t size, size_t nmemb, void *userdata)) {
	CURLcode status = curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	if (status == CURLE_OK) {
		status = curl_easy_setopt(curl, CURLOPT_WRITEDATA, user_struct);
		if (status == CURLE_OK) {
			status = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
		}
	}

	return status;
}

#endif
