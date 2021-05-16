KEYMAP_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_features.mk
include $(KEYMAP_LOCAL_FEATURES_MK)
