/* This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Force n-key rollover
#define FORCE_NKRO

#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE // Sets the default effect mode

#define RGB_MATRIX_DEFAULT_HUE 24                         // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 255                        // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL 127                        // Sets the default brightness value, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 127                        // Sets the default animation speed, if none has been set