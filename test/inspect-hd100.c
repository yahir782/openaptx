/*
 * inspect-hd100.c
 * Copyright (c) 2017-2018 Arkadiusz Bokowy
 *
 * This file is a part of [open]aptx.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#include "inspect-hd100.h"

#include <stdio.h>
#include <string.h>

static void hexdump(const void *mem, size_t n) {
	while (n--) {
		fprintf(stderr, "%02x", *(uint8_t *)mem & 0xFF);
		mem += 1;
	}
}

static int int32diff(const char *label, int32_t a, int32_t b) {
	if (a == b)
		return 0;
	fprintf(stderr, "%s: %d != %d\n", label, a, b);
	return a - b;
}

static int pmemdiff(const char *label, const void *a, const void *b) {
	if (a == b)
		return 0;
	fprintf(stderr, "%s: %p != %p\n", label, a, b);
	return a - b;
}

int aptXHD_mem_cmp(
		const char *label,
		const void *a,
		const void *b,
		size_t n) {

	int ret = 0;

	if (a == b)
		return ret;
	if ((ret = memcmp(a, b, n)) == 0)
		return ret;
	fprintf(stderr, "%s: ", label);
	hexdump(a, n);
	fprintf(stderr, " != ");
	hexdump(b, n);
	fprintf(stderr, "\n");

	return ret;
}

int aptXHD_prediction_filter_100_cmp(
		const char *label,
		const aptXHD_prediction_filter_100 *a,
		const aptXHD_prediction_filter_100 *b) {

	char tmp[128];
	int ret = 0;

	sprintf(tmp, "%s.width", label);
	ret |= int32diff(tmp, a->width, b->width);
	sprintf(tmp, "%s.arr1", label);
	ret |= aptXHD_mem_cmp(tmp, a->arr1, b->arr1, sizeof(a->arr1));
	sprintf(tmp, "%s.sign1", label);
	ret |= int32diff(tmp, a->sign1, b->sign1);
	sprintf(tmp, "%s.sign2", label);
	ret |= int32diff(tmp, a->sign2, b->sign2);
	sprintf(tmp, "%s.unk2", label);
	ret |= int32diff(tmp, a->unk2, b->unk2);
	sprintf(tmp, "%s.unk3", label);
	ret |= int32diff(tmp, a->unk3, b->unk3);
	sprintf(tmp, "%s.subband_param_unk3_2", label);
	ret |= int32diff(tmp, a->subband_param_unk3_2, b->subband_param_unk3_2);
	sprintf(tmp, "%s.arr2", label);
	ret |= aptXHD_mem_cmp(tmp, a->arr2, b->arr2, sizeof(a->arr2));
	sprintf(tmp, "%s.i", label);
	ret |= int32diff(tmp, a->i, b->i);
	sprintf(tmp, "%s.subband_param_unk3_3", label);
	ret |= int32diff(tmp, a->subband_param_unk3_3, b->subband_param_unk3_3);
	sprintf(tmp, "%s.unk5", label);
	ret |= int32diff(tmp, a->unk5, b->unk5);
	sprintf(tmp, "%s.unk6", label);
	ret |= int32diff(tmp, a->unk6, b->unk6);
	sprintf(tmp, "%s.unk7", label);
	ret |= int32diff(tmp, a->unk7, b->unk7);
	sprintf(tmp, "%s.unk8", label);
	ret |= int32diff(tmp, a->unk8, b->unk8);

	return ret;
}

int aptXHD_inverter_100_cmp(
		const char *label,
		const aptXHD_inverter_100 *a,
		const aptXHD_inverter_100 *b) {

	char tmp[128];
	int ret = 0;

	sprintf(tmp, "%s.subband_param_p1", label);
	ret |= pmemdiff(tmp, a->subband_param_p1, b->subband_param_p1);
	sprintf(tmp, "%s.subband_param_bit16_sl1", label);
	ret |= aptXHD_mem_cmp(tmp, a->subband_param_bit16_sl1, b->subband_param_bit16_sl1, sizeof(*a->subband_param_bit16_sl1) * 5 /* XXX: arbitrary size */);
	sprintf(tmp, "%s.subband_param_dith16_sf1", label);
	ret |= aptXHD_mem_cmp(tmp, a->subband_param_dith16_sf1, b->subband_param_dith16_sf1, sizeof(*a->subband_param_dith16_sf1) * 5 /* XXX: arbitrary size */);
	sprintf(tmp, "%s.subband_param_incr16", label);
	ret |= aptXHD_mem_cmp(tmp, a->subband_param_incr16, b->subband_param_incr16, sizeof(*a->subband_param_incr16) * 5 /* XXX: arbitrary size */);
	sprintf(tmp, "%s.subband_param_unk1", label);
	ret |= int32diff(tmp, a->subband_param_unk1, b->subband_param_unk1);
	sprintf(tmp, "%s.subband_param_unk2", label);
	ret |= int32diff(tmp, a->subband_param_unk2, b->subband_param_unk2);
	sprintf(tmp, "%s.unk9", label);
	ret |= int32diff(tmp, a->unk9, b->unk9);
	sprintf(tmp, "%s.unk10", label);
	ret |= int32diff(tmp, a->unk10, b->unk10);
	sprintf(tmp, "%s.unk11", label);
	ret |= int32diff(tmp, a->unk11, b->unk11);
	sprintf(tmp, "%s.log", label);
	ret |= aptXHD_mem_cmp(tmp, a->log, b->log, sizeof(*a->log) * 32);

	return ret;
}

int aptXHD_quantizer_100_cmp(
		const char *label,
		const aptXHD_quantizer_100 *a,
		const aptXHD_quantizer_100 *b) {

	char tmp[128];
	int ret = 0;

	sprintf(tmp, "%s.bits", label);
	ret |= int32diff(tmp, a->subband_param_bits, b->subband_param_bits);
	sprintf(tmp, "%s.subband_param_p1", label);
	ret |= pmemdiff(tmp, a->subband_param_p1, b->subband_param_p1);
	sprintf(tmp, "%s.subband_param_bit16_sl1", label);
	ret |= aptXHD_mem_cmp(tmp, a->subband_param_bit16_sl1, b->subband_param_bit16_sl1, sizeof(*a->subband_param_bit16_sl1) * 5 /* XXX: arbitrary size */);
	sprintf(tmp, "%s.subband_param_p3", label);
	ret |= pmemdiff(tmp, a->subband_param_p3, b->subband_param_p3);
	sprintf(tmp, "%s.subband_param_mLamb16", label);
	ret |= aptXHD_mem_cmp(tmp, a->subband_param_mLamb16, b->subband_param_mLamb16, sizeof(*a->subband_param_mLamb16) * 5 /* XXX: arbitrary size */);
	sprintf(tmp, "%s.unk1", label);
	ret |= int32diff(tmp, a->unk1, b->unk1);
	sprintf(tmp, "%s.unk2", label);
	ret |= int32diff(tmp, a->unk2, b->unk2);
	sprintf(tmp, "%s.unk3", label);
	ret |= int32diff(tmp, a->unk3, b->unk3);

	return ret;
}

int aptXHD_subband_encoder_100_cmp(
		const char *label,
		const aptXHD_subband_encoder_100 *a,
		const aptXHD_subband_encoder_100 *b) {

	char tmp[128];
	int ret = 0;
	size_t i;

	for (i = 0; i < __APTXHD_SUBBAND_MAX; i++) {
		sprintf(tmp, "%s.processor[%zd].filter", label, i);
		ret |= aptXHD_prediction_filter_100_cmp(tmp, &a->processor[i].filter, &b->processor[i].filter);
		sprintf(tmp, "%s.processor[%zd].inverter", label, i);
		ret |= aptXHD_inverter_100_cmp(tmp, &a->processor[i].inverter, &b->processor[i].inverter);
	}
	sprintf(tmp, "%s.codeword", label);
	ret |= int32diff(tmp, a->codeword, b->codeword);
	sprintf(tmp, "%s.dither_sign", label);
	ret |= int32diff(tmp, a->dither_sign, b->dither_sign);
	for (i = 0; i < __APTXHD_SUBBAND_MAX; i++) {
		sprintf(tmp, "%s.dither[%zd]", label, i);
		ret |= int32diff(tmp, a->dither[i], b->dither[i]);
	}
	for (i = 0; i < __APTXHD_SUBBAND_MAX; i++) {
		sprintf(tmp, "%s.quantizer[%zd]", label, i);
		ret |= aptXHD_quantizer_100_cmp(tmp, &a->quantizer[i], &b->quantizer[i]);
	}

	return ret;
}

int aptXHD_QMF_analyzer_100_cmp(
		const char *label,
		const aptXHD_QMF_analyzer_100 *a,
		const aptXHD_QMF_analyzer_100 *b) {

	char tmp[128];
	int ret = 0;
	size_t i;

	for (i = 0; i < 2; i++) {
		sprintf(tmp, "%s.outer[%zd]", label, i);
		ret |= aptXHD_mem_cmp(tmp, &a->outer[i], &b->outer[i], sizeof(a->outer[i]));
	}
	for (i = 0; i < 4; i++) {
		sprintf(tmp, "%s.inner[%zd]", label, i);
		ret |= aptXHD_mem_cmp(tmp, &a->inner[i], &b->inner[i], sizeof(a->inner[i]));
	}
	sprintf(tmp, "%s.i_inner", label);
	ret |= int32diff(tmp, a->i_inner, b->i_inner);
	sprintf(tmp, "%s.i_outer", label);
	ret |= int32diff(tmp, a->i_outer, b->i_outer);

	return ret;
}

int aptXHD_encoder_100_cmp(
		const char *label,
		const aptXHD_encoder_100 *a,
		const aptXHD_encoder_100 *b) {

	char tmp[128];
	int ret = 0;
	size_t i;

	if (a == b)
		return ret;

	sprintf(tmp, "%s.swap", label);
	ret |= int32diff(tmp, a->swap, b->swap);
	sprintf(tmp, "%s.sync", label);
	ret |= int32diff(tmp, a->sync, b->sync);
	for (i = 0; i < APTXHD_CHANNELS; i++) {
		sprintf(tmp, "%s.encoder[%zd]", label, i);
		ret |= aptXHD_subband_encoder_100_cmp(tmp, &a->encoder[i], &b->encoder[i]);
	}
	for (i = 0; i < APTXHD_CHANNELS; i++) {
		sprintf(tmp, "%s.analyzer[%zd]", label, i);
		ret |= aptXHD_QMF_analyzer_100_cmp(tmp, &a->analyzer[i], &b->analyzer[i]);
	}

	return ret;
}
