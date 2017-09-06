//
//  ZYKernelDefines.h
//  Pods
//
//  Created by RangerChiong on 2017/9/6.
//
//

#ifndef ZYKernelDefines_h
#define ZYKernelDefines_h

#pragma mark-   common use

#define App_KeyWindow   [[UIApplication sharedApplication].delegate window]

// 常用系统的高度
#define Height_KeyBoard         216.0f
#define Height_TabBar           49.0f
#define Height_NavigationBar    44.0f
#define Height_StatusBar        20.0f
#define Height_TopBar           64.0f

#define Screen_Bounds   ([UIScreen mainScreen].bounds)
#define Screen_Size     (Screen_Bounds.size)
#define Screen_Width    (Screen_Size.width)
#define Screen_Height   (Screen_Size.height)
#define Screen_Scale    ([[UIScreen mainScreen] scale])

// 线条的高度
#define Height_Line   ((1.0f / [UIScreen mainScreen].scale) / 2.0f)

// 字体
#define Font_System(size)      [UIFont systemFontOfSize:size]
#define Font_System_Bold(size) [UIFont boldSystemFontOfSize:size]

// 16进制颜色转UIColor  ColorHex(0x000000)
#define Color_Hex(hexValue)   [UIColor colorWithRed:((float)((hexValue & 0xFF0000) >> 16)) / 255.0 green:((float)((hexValue & 0xFF00) >> 8)) / 255.0 blue:((float)(hexValue & 0xFF)) / 255.0 alpha:1.0]
// RGB颜色
#define Color_RGBA(r,g,b,a)   [UIColor colorWithRed:r/255.0f green:g/255.0f blue:b/255.0f alpha:a]
#define Color_RGB(r,g,b)      Color_RGBA(r,g,b,1.0f)
#define Color_Random          Color_RGB(arc4random_uniform(256), arc4random_uniform(256), arc4random_uniform(256))

//读取图片
#define Image_Named(name) [UIImage imageNamed:name]
#define Image_File(file, ext) [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:file ofType:ext]]
#define Image_FileFullName(A) [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:A ofType:nil]]

// 沙盒路径
#define SandBox_Documents [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject]
#define SandBox_Caches    [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject]
#define SandBox_Temporary NSTemporaryDirectory()
#define SandBox_Root      NSHomeDirectory()


#define Safe_Block(block, ...)  block ? block(__VA_ARGS__) : nil
#define Safe_Return(_obj_)      if (_obj_) return _obj_
#define Safe_Delegate(name, selector)   (name && [name respondsToSelector:selector]) ? YES : NO
#define Safe_Delegate_Default(selector)  (_delegate && [_delegate respondsToSelector:selector]) ? YES : NO

#pragma mark-  Device

// 操作系统版本号
#define IOS_VERSION ([[[UIDevice currentDevice] systemVersion] floatValue])

/// 使用iOS8 API时要加`ifdef IOS8_SDK_ALLOWED`的判断

#ifndef __IPHONE_8_0
#define __IPHONE_8_0 80000
#endif
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_8_0
#define IOS8_SDK_ALLOWED YES
#endif


/// 使用iOS9 API时要加`ifdef IOS9_SDK_ALLOWED`的判断

#ifndef __IPHONE_9_0
#define __IPHONE_9_0 90000
#endif
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_9_0
#define IOS9_SDK_ALLOWED YES
#endif


/// 使用iOS10 API时要加`ifdef IOS10_SDK_ALLOWED`的判断

#ifndef __IPHONE_10_0
#define __IPHONE_10_0 100000
#endif
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0
#define IOS10_SDK_ALLOWED YES
#endif

#pragma mark-  print log

#ifdef DEBUG

#define IS_DEBUG YES

#define DLog(format, ...) do {                                           \
fprintf(stderr, "<File:[%s] : Line:[%d]> ---%s\n",                          \
[[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String],  \
__LINE__, __func__);                                                        \
(NSLog)((format), ##__VA_ARGS__);                                           \
fprintf(stderr, "-------\n");                                               \
} while (0)

#define ULog(fmt, ...)  { UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"%s\n [Line %d] ", __PRETTY_FUNCTION__, __LINE__] message:[NSString stringWithFormat:fmt, ##__VA_ARGS__]  delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil]; [alert show]; }

#else

#define IS_DEBUG NO
#define DLog(...)
#define ULog(...)

#endif

#pragma mark-  utils

// 获取变量名     转换成NSString 用%s格式化
#define Variable_Name(type)  #type

// 使用时 Key_Path(ObjA.property1.property2)  获取对象的属性的字符串  用在KVO等场景
//#define Key_Path(keypath) (strchr(#keypath, '.') + 1)
#define Key_Path(OBJ, PATH)  (((void)(NO && ((void)OBJ.PATH, NO)), # PATH))

#define IgnorePerformSelectorLeakWarning(__code__) \
do { \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") \
__code__ \
_Pragma("clang diagnostic pop") \
} while (0)

#if defined(DEBUG) && !defined(NDEBUG)
#define ol_keywordify autoreleasepool {}
#else
#define ol_keywordify try {} @catch (...) {}
#endif

#define metamacro_concat(A, B)   A ## B

#define weakify(_arg_) \
ol_keywordify \
__weak typeof(_arg_) metamacro_concat(weak, _arg_) = _arg_;


#define strongifyAndReturnIfNil(_arg_) \
ol_keywordify \
__strong typeof(metamacro_concat(weak, _arg_)) _arg_ = metamacro_concat(weak, _arg_);\
if (!_arg_) return


#endif /* ZYKernelDefines_h */
