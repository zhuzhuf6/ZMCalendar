//
//  ZMCalendarDefaultMacro.h
//  ZMCalendar
//
//  Created by 朱敏 on 16/1/30.
//  Copyright (c) 2016年 Arron Zhu. All rights reserved.
//

#ifndef ZMCalendar_ZMCalendarDefaultMacro_h
#define ZMCalendar_ZMCalendarDefaultMacro_h

#define kDefaultFont           13
#define kMasking               10
#define kItemSpacing           5
#define kDefaultCalendarHeight 300
#define kDefaultHeight         44
#define kWeeklyDays            7
#define kZero                  0
#define kOneDayTimeInterval    (60 * 60 * 24)

// NSString
#define kStringFromClass(class)   @#(class)
#define kUnnullString(parameter)  (parameter).length ? (parameter) : @""
#define kString(parameter)        [NSString stringWithFormat:@"%@", (parameter)]

// 屏幕宽、高
#define kScreen_bounds      ([[UIScreen mainScreen] bounds])
#define kScreen_width       ([[UIScreen mainScreen] bounds].size.width)
#define kScreen_height      ([[UIScreen mainScreen] bounds].size.height)
#define kScreenScale        ([[UIScreen mainScreen] scale])

#endif
