/*
 * Copyright 2014 Emil Edholm <emil@edholm.it>
 */
#pragma once
#ifndef __VOLUME_H__
#define __VOLUME_H__
#include <alsa/asoundlib.h>
#include "generator.hh"

 class Volume: public Generator {
private:
    snd_mixer_t *h_mixer;
    snd_mixer_selem_id_t *sid;
    snd_mixer_elem_t *elem;

    const char *ATTACH = "default";
    const snd_mixer_selem_channel_id_t CHANNEL = SND_MIXER_SCHN_FRONT_LEFT;
    const char *SELEM_NAME = "Master";

    bool setup_failed;

    void init_mixer();
    void error_close(const char*, int, snd_mixer_t*);
    bool is_muted();
    int get_volume();
 public:
    std::string generate_json();
 };
#endif
