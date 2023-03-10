/*
 * Tulip Indicators
 * https://tulipindicators.org/
 * Copyright (c) 2010-2017 Tulip Charts LLC
 * Lewis Van Winkle (LV@tulipcharts.org)
 *
 * This file is part of Tulip Indicators.
 *
 * Tulip Indicators is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Tulip Indicators is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tulip Indicators.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../indicators.h"
#include "../utils/minmax.h"



int ti_wad_start(TI_REAL const *options) {
    (void)options;
    return 1;
}


int ti_wad(int size, TI_REAL const *const *inputs, TI_REAL const *options, TI_REAL *const *outputs) {
    const TI_REAL *high = inputs[0];
    const TI_REAL *low = inputs[1];
    const TI_REAL *close = inputs[2];

    (void)options;

    if (size <= ti_wad_start(options)) return TI_OKAY;

    TI_REAL *output = outputs[0];
    TI_REAL sum = 0;
    TI_REAL yc = close[0];

    int i;
    for (i = 1; i < size; ++i) {
        const TI_REAL c = close[i];

        if (c > yc) {
            sum += c - MIN(yc, low[i]);
        } else if (c < yc) {
            sum += c - MAX(yc, high[i]);
        } else {
            /* No change */
        }

        *output++ = sum;

        yc = close[i];
    }


    assert(output - outputs[0] == size - ti_wad_start(options));
    return TI_OKAY;
}
