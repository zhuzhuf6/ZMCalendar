//
//  ZMCalendarMacro.h
//  ZMCalendar
//
//  Created by 朱敏 on 16/1/10.
//  Copyright (c) 2016年 Arron Zhu. All rights reserved.
//

#import "ZMCalendarDefaultMacro.h"

#ifndef ZMCalendar_ZMCalendarMacro_h
#define ZMCalendar_ZMCalendarMacro_h

#ifdef __cplusplus
#define ZM_EXTERN_C_BEGIN extern "c" {
#define ZM_EXTERN_C_END   }
#else
#define ZM_EXTERN_C_BEGIN
#define ZM_EXTERN_C_END
#endif

ZM_EXTERN_C_BEGIN

#ifdef DEBUG
#define ZMLog(format, ...) do {                                                                          \
                             fprintf(stderr, "<%s : %d> %s\n",                                           \
                             [[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String],  \
                             __LINE__, __func__);                                                        \
                             (NSLog)((format), ##__VA_ARGS__);                                           \
                             fprintf(stderr, "-------\n");                                               \
                             } while (0)
#else
#define ZMLog(format, ...)
#endif


#define ZMAssertNil(condition, description, ...) NSAssert(!(condition), (description), ##__VA_ARGS__)
#define ZMCAssertNil(condition, description, ...) NSCAssert(!(condition), (description), ##__VA_ARGS__)

#define ZMAssertNotNil(condition, description, ...) NSAssert((condition), (description), ##__VA_ARGS__)
#define ZMCAssertNotNil(condition, description, ...) NSCAssert((condition), (description), ##__VA_ARGS__)

/**
 Add this macro before each category implementation, so we don't have to use
 -all_load or -force_load to load object files from static libraries that only
 contain categories and no classes.
 *******************************************************************************
 给分类文件加上一个虚拟的类
 */
#ifndef ZMSYNTH_DUMMY_CLASS
#define ZMSYNTH_DUMMY_CLASS(_name_) \
@interface ZMSYNTH_DUMMY_CLASS_ ## _name_ : NSObject @end \
@implementation ZMSYNTH_DUMMY_CLASS_ ## _name_ @end
#endif

/**
 Synthsize a dynamic object property in @implementation scope.
 It allows us to add custom properties to existing classes in categories.
 *******************************************************************************
 动态的添加属性
 @end
 */
#ifndef ZMSYNTH_DYNAMIC_PROPERTY_OBJECT
#define ZMSYNTH_DYNAMIC_PROPERTY_OBJECT(_getter_, _setter_, _association_, _type_) \
- (void)_setter_ : (_type_)object { \
    [self willChangeValueForKey:@#_getter_]; \
    objc_setAssociatedObject(self, _cmd, object, OBJC_ASSOCIATION_ ## _association_); \
    [self didChangeValueForKey:@#_getter_]; \
    } \
- (_type_)_getter_ { \
    return objc_getAssociatedObject(self, @selector(_setter_:)); \
}
#endif

/**
 Singleton
 *******************************************************************************
 单利
 */
#define SingletonH(methodName) +(instancetype)shared##methodName;
#if __has_feature(objc_arc)
#define SingletonM(methodName) \
static id _instace = nil; \
- (id)allocWithZone:(struct NSZone *)zone \
{ \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        _instace = [super allocWithZone:zone];\
    }); \
    return _instace; \
} \
\
+ (instancetype)shared##methodName \
{ \
    return [[self alloc] init]; \
} \
- (id)copyWithZone:(struct NSZone *)zone \
{ \
    return _instace; \
} \
\
- (id)mutableCopyWithZone:(struct NSZone *)zone \
{ \
    return _instace; \
}

#else
#define SingletonM(methodName) \
static id _instace = nil; \
-(id)allocWithZone:(struct NSZone *)zone \
{ \
    static dispatch_once_t onceToken; \
    dispatch_once(&onceToken, ^{ \
        _instace = [super allocWithZone:zone]; \
    }); \
    return _instace; \
} \
\
+ (instancetype)shared##methodName \
{ \
    return [[self alloc] init]; \
} \
\
- (oneway void)release \
{ \
    \
} \
\
- (id)retain \
{ \
    return self; \
} \
\
- (NSUInteger)retainCount \
{ \
    return 1; \
} \
- (id)copyWithZone:(struct NSZone *)zone \
{ \
    return _instace; \
} \
\
- (id)mutableCopyWithZone:(struct NSZone *)zone \
{ \
    return _instace; \
}

#endif



ZM_EXTERN_C_END
#endif
