/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "opentx.h"

void pxx2ModuleRequiredScreen(event_t event)
{
  lcdClear();
  lcdDrawCenteredText(15, "THIS FEATURE REQUIRES");
  lcdDrawCenteredText(30, "ACCESS UPGRADE ON");
  lcdDrawCenteredText(45, "YOUR INTERNAL MODULE");

  if(event == EVT_KEY_FIRST(KEY_EXIT)) {
    killEvents(event);
    popMenu();
  }
}

void addRadioTool(uint8_t index, const char * label, void (* tool)(event_t event), event_t event)
{
  int8_t sub = menuVerticalPosition - HEADER_LINE;
  LcdFlags attr = (sub == index ? INVERS : 0);
  coord_t y = MENU_HEADER_HEIGHT + 1 + index * FH;
  lcdDrawNumber(3, y, index + 1, LEADING0|LEFT, 2);
  lcdDrawText(3*FW, y, label, (sub == index ? INVERS  : 0));
  if (attr && s_editMode > 0) {
    s_editMode = 0;
    pushMenu(tool);
  }
}

void menuRadioTools(event_t event)
{
  SIMPLE_MENU("TOOLS", menuTabGeneral, MENU_RADIO_TOOLS, HEADER_LINE + 2);

#if defined(PXX2) && !(defined(PCBX9D) || defined(PCBX9DP) || defined(PCBX9E) || defined(PCBX7) || (defined(PCBXLITE) && !defined(PCBXLITES)))
  addRadioTool(0, "Spectrum Analyser", menuRadioSpectrumAnalyser, event);
  addRadioTool(1, "Power Meter", menuRadioPowerMeter, event);
#endif
}