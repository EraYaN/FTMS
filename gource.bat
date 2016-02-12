@echo off
title Gource FTMS
"../gource/gource.exe" --fullscreen -3840x2160 --stop-at-end --file-idle-time 6000 --multi-sampling --key --max-files 0 --seconds-per-day 6
pause