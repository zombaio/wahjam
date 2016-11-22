/*
    Copyright (C) 2016 Stefan Hajnoczi <stefanha@gmail.com>

    Wahjam is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Wahjam is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Wahjam; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* Prevent screen from going to sleep.  See
 * https://developer.apple.com/library/content/qa/qa1340/_index.html
 */

#include <IOKit/pwr_mgt/IOPMLib.h>

static CFStringRef activityName = CFSTR("Jam Session");
static IOPMAssertionID assertionID;

void screenPreventSleep()
{
  if (assertionID != kIOPMNullAssertionID) {
    return;
  }

  IOPMAssertionCreateWithName(kIOPMAssertionTypeNoDisplaySleep,
                              kIOPMAssertionLevelOn,
                              activityName,
                              &assertionID);
}

void screenAllowSleep()
{
  if (assertionID == kIOPMNullAssertionID) {
    return;
  }

  IOPMAssertionRelease(assertionID);
  assertionID = kIOPMNullAssertionID;
}
