#include "../../includes/others/mac/mac.h"

#import <CoreServices/CoreServices.h>
#import <Carbon/Carbon.h>

CGKeyCode keyCodeForCharWithLayout(const short c, const UCKeyboardLayout *uchrHeader);
CGKeyCode keyCodeForChar(const short c);

Mac::Mac(QWidget* w)
{
    if (w == NULL)
    {
        return;
    }
    NSView *nsview = (NSView *)w->winId();
    NSWindow *nswindow = [nsview window];
    if (QSysInfo::MacintoshVersion >= QSysInfo::MV_10_7)
    {
        [nswindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
    }
}

CGKeyCode keyCodeForChar(const short c)
{
    CFDataRef currentLayoutData;
    TISInputSourceRef currentKeyboard = TISCopyCurrentKeyboardInputSource();

    if (currentKeyboard == NULL)
    {
        fputs("Could not find keyboard layout\n", stderr);
        return UINT16_MAX;
    }

    currentLayoutData = (CFDataRef)TISGetInputSourceProperty(currentKeyboard,
                                                             kTISPropertyUnicodeKeyLayoutData);
    CFRelease(currentKeyboard);
    if (currentLayoutData == NULL)
    {
        fputs("Could not find layout data\n", stderr);
        return UINT16_MAX;
    }

    return keyCodeForCharWithLayout(c,
                                    (const UCKeyboardLayout *)CFDataGetBytePtr(currentLayoutData));
}

/* Beware! Messy, incomprehensible code ahead! */
CGKeyCode keyCodeForCharWithLayout(const short c, const UCKeyboardLayout *uchrHeader)
{
    uint8_t *uchrData = (uint8_t *)uchrHeader;
    UCKeyboardTypeHeader *uchrKeyboardList = (UCKeyboardTypeHeader*)uchrHeader->keyboardTypeList;

    /* Loop through the keyboard type list. */
    ItemCount i, j;
    for (i = 0; i < uchrHeader->keyboardTypeCount; ++i)
    {
        /* Get a pointer to the keyToCharTable structure. */
        UCKeyToCharTableIndex *uchrKeyIX = (UCKeyToCharTableIndex *)
                (uchrData + (uchrKeyboardList[i].keyToCharTableIndexOffset));

        /* Not sure what this is for but it appears to be a safeguard... */
        UCKeyStateRecordsIndex *stateRecordsIndex;
        if (uchrKeyboardList[i].keyStateRecordsIndexOffset != 0)
        {
            stateRecordsIndex = (UCKeyStateRecordsIndex *)
                    (uchrData + (uchrKeyboardList[i].keyStateRecordsIndexOffset));

            if ((stateRecordsIndex->keyStateRecordsIndexFormat) !=
                    kUCKeyStateRecordsIndexFormat)
            {
                stateRecordsIndex = NULL;
            }
        } else {
            stateRecordsIndex = NULL;
        }

        /* Make sure structure is a table that can be searched. */
        if ((uchrKeyIX->keyToCharTableIndexFormat) != kUCKeyToCharTableIndexFormat)
        {
            continue;
        }

        /* Check the table of each keyboard for character */
        for (j = 0; j < uchrKeyIX->keyToCharTableCount; ++j)
        {
            UCKeyOutput *keyToCharData =
                    (UCKeyOutput *)(uchrData + (uchrKeyIX->keyToCharTableOffsets[j]));

            /* Check THIS table of the keyboard for the character. */
            UInt16 k;
            for (k = 0; k < uchrKeyIX->keyToCharTableSize; ++k)
            {
                /* Here's the strange safeguard again... */
                if ((keyToCharData[k] & kUCKeyOutputTestForIndexMask) ==
                        kUCKeyOutputStateIndexMask)
                {
                    long keyIndex = (keyToCharData[k] & kUCKeyOutputGetIndexMask);
                    if (stateRecordsIndex != NULL &&
                            keyIndex <= (stateRecordsIndex->keyStateRecordCount))
                    {
                        UCKeyStateRecord *stateRecord = (UCKeyStateRecord *)
                                (uchrData +
                                 (stateRecordsIndex->keyStateRecordOffsets[keyIndex]));

                        if ((stateRecord->stateZeroCharData) == c)
                        {
                            return (CGKeyCode)k;
                        }
                    } else if (keyToCharData[k] == c)
                    {
                        return (CGKeyCode)k;
                    }
                } else if (((keyToCharData[k] & kUCKeyOutputTestForIndexMask)
                            != kUCKeyOutputSequenceIndexMask) &&
                           keyToCharData[k] != 0xFFFE &&
                           keyToCharData[k] != 0xFFFF &&
                           keyToCharData[k] == c)
                {
                    return (CGKeyCode)k;
                }
            }
        }
    }

    return UINT16_MAX;
}

void Mac::showNotification(char* pTitle, char* pMessage)
{
    if (QSysInfo::MacintoshVersion >= QSysInfo::MV_10_7)
    {
        NSUserNotification *notification = [[NSUserNotification alloc] init];
        [notification setTitle:[NSString stringWithUTF8String:pTitle]];
        [notification setInformativeText:[NSString stringWithUTF8String:pMessage]];
        [notification setDeliveryDate:[NSDate dateWithTimeInterval:.1 sinceDate:[NSDate date]]];
        [notification setSoundName:NSUserNotificationDefaultSoundName];
        NSUserNotificationCenter *center = [NSUserNotificationCenter defaultUserNotificationCenter];
        [center scheduleNotification:notification];
    }
}

int Mac::convertToCGKeyCode(short keyCode)
{
    return keyCodeForChar(keyCode);
}

void Mac::generateKeyEvent(unsigned short keyCode, bool shiftModifier, bool ctrlModifier, bool metaModifier, bool altModifier, bool altGrModifier)
{
    /* Source */
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

    /* Modifiers */
    CGEventFlags shift=0;
    if (shiftModifier)
    {
        shift = kCGEventFlagMaskShift;
    }
    CGEventFlags ctrl=0;
    if (ctrlModifier)
    {
        ctrl = kCGEventFlagMaskControl;
    }
    CGEventFlags option=0;
    if (altModifier)
    {
        option = kCGEventFlagMaskAlternate;
    }
    CGEventFlags cmd=0;
    if (metaModifier)
    {
        cmd = kCGEventFlagMaskCommand;
    }
    CGEventFlags fn=0;
    if (altGrModifier)
    {
        fn = kCGEventFlagMaskSecondaryFn;
    }

    /* Down event */
    CGEventRef commandDown = CGEventCreateKeyboardEvent(source, keyCode, YES);
    CGEventSetFlags(commandDown, shift | ctrl | option | cmd | fn);
    CGEventSetType(commandDown, kCGEventKeyDown);

    /* Up event */
    CGEventRef commandUp = CGEventCreateKeyboardEvent(source, keyCode, NO);
    CGEventSetFlags(commandUp, shift | ctrl | option | cmd | fn);
    CGEventSetType(commandUp, kCGEventKeyUp);

    /* Post events */
    CGEventPost(kCGHIDEventTap, commandDown);
    CGEventPost(kCGHIDEventTap, commandUp);

    /* Release events */
    CFRelease(commandUp);
    CFRelease(commandDown);
    CFRelease(source);
}
