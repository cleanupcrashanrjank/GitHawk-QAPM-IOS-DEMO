//
//  QAPM.h
//  QAPM
//
//  SDK Version 3.1.0 Inner_Version
//
//  Created by Cass on 2018/5/18.
//  Copyright © 2018年 cass. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "QAPMConfig.h"
#import "QAPMUtilities.h"

NS_ASSUME_NONNULL_BEGIN

@interface QAPM : NSObject

/**
 使用指定配置初始化QAPM
 
 * @param appKey 注册QAPM分配的唯一标识
 */
+ (void)startWithAppKey:(NSString * __nonnull)appKey;

/**
 注册SDK内部日志回调，用于输出SDK内部日志
 
 @param logger 外部的日志打印方法
 */
+ (void)registerLogCallback:(QAPM_Log_Callback)logger;

/**
 更新设置用户标识
 当登录后，可以使用该方法更新userId
 
 *  @param userId 用户标识
 */
+ (void)updateUserIdentifier:(NSString *)userId;

+ (void)addUserInfo:(NSDictionary *)userInfo;

+ (void)updateDeviceID:(NSString *)deviceID;

/**
 SDK 版本信息

 @return SDK版本号
 */
+ (NSString *)sdkVersion;

/**
 上报检测事件回调。提供用于Athena SDK使用
 
 @param callback eventId此次事件唯一Id, type事件类型。
 */
+ (void)setUploadEventCallback:(QAPMUploadEventCallback)callback;

/**
 监控功能开启状态回调。提供用于Athena SDK使用
 
 @param callback state 功能状态, type 功能类相关。
 */
+ (void)monitorStartCallback:(QAPMMonitorStartCallback)callback;

+ (BOOL)monitorEnableWithType:(QAPMMonitorType)type;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
@interface QAPMBlueProfile : NSObject

/**
 开始记录掉帧，建议滑动开始时调用
 
 * @param stage 用来标识当前页面(一般为当前VC类名）
 */
+ (void)beginTrackingWithStage:(NSString *)stage;

/**
 结束记录掉帧，滑动结束时调用
 
 * @param stage 用来标识当前页面(一般为当前VC类名）
 */
+ (void)stopTrackingWithStage:(NSString *)stage;

/**
 更新所有场景的掉帧堆栈开关（除滑动外其它场景上报时的关键字为"others"),默认开启。
 更新[QAPMConfig getInstance].blueConfig.monitorOtherStageEnable
 在退后台的时候由于线程优先级降低，会使检测时间产生极大误差，强烈建议退后台的时候调用[QAPMBlueProfile updateMonitorOtherStageEnable:NO]关闭监控，在进前台时可以恢复监控！
 */
+ (void)updateMonitorOtherStageEnable:(BOOL)enable;

/**
 滑动场景区分，如果不需要则设置为0
 滑动结束时调用
 
 * @param type 设置为0时只有“Normal_Scroll"的数据，当设置为其他值时，掉帧数据里面会多一个类型为"UserDefineScollType_x"的数据
 */
+ (void)setScrollType:(int32_t)type;


@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@protocol QAPMYellowProfileDelegate <NSObject>

/**
 VC发生泄漏时的回调接口

 @param vc VC类名
 @param seq VC操作序列
 @param stack 内存方法的堆栈信息
 */
- (void)handleVCLeak:(UIViewController *)vc oprSeq:(NSString *)seq stackInfo:(NSString *)stack;

@end

@interface QAPMYellowProfile : NSObject

/**
 设置VC白名单类(对于需要在VC退出后驻留内存的VC)

 @param set 白名单VC，set中的对象为NSString对象，是白名单VC类名，如果没有白名单则不设置
 @param array 白名单基类VC，array中的对象为NSString对象，是白名单VC基类名，这些基类对象的所有子类都添加白名单
 */
+ (void)setWhiteVCList:(NSSet *)set baseVCArray:(NSArray *)array;

/**
 针对白名单VC，可自定义检测时机，非白名单VC无需实现
 注意：该方法在VC退出后调用，注意不要在dealloc方法中调用改方法，因为VC内存泄漏时无法执行dealloc

 @param VC 白名单VC
 */
+ (void)startVCLeakObservation:(UIViewController *)VC;

/**
 设置该对象为白名单对象，无需监控

 @param obj 白名单对象
 */
+ (void)markedAsWhiteObj:(NSObject *)obj;


/**
 设置QAPMYellowProfileDelegate

 @param delegate delegate
 */
+ (void)setYellowProfileDelegate:(id<QAPMYellowProfileDelegate>)delegate;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QAPMSigkillProfile : NSObject

/**
 请在Crash组件捕获到crash后调用该方法，如果使用QAPM Crash功能则不需要设置
 */
+ (void)appDidCrashed;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QAPMTimeStatisticProfile : NSObject

/**
 开始打点统计时间

 @param stage 用来标识当前打点场景(开始与结束stage必须一致才能统计计算时间)
 */
+ (void)beginStatisticTimeWithStage:(NSString * __nonnull)stage;

/**
 开始打点统计时间

 @param stage 用来标识当前打点场景(开始与结束stage必须一致才能统计计算时间)
 @param identifier 标识当前打点场景的额外标记(开始与结束stage，identifier必须一致才能统计计算时间)
 */
+ (void)beginStatisticTimeWithStage:(NSString * __nonnull)stage identifier:(NSString * __nonnull)identifier;

/**
 结束打点统计时间

 @param stage 用来标识当前打点场景(开始与结束stage必须一致才能统计计算时间)
 */
+ (void)stopStatisticTimeWithStage:(NSString * __nonnull)stage;

/**
 结束打点统计时间

 @param stage 用来标识当前打点场景(开始与结束stage必须一致才能统计计算时间)
 @param identifier 标识当前打点场景的额外标记(开始与结束stage，identifier必须一致才能统计计算时间)
 */
+ (void)stopStatisticTimeWithStage:(NSString * __nonnull)stage identifier:(NSString * __nonnull)identifier;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QAPMQQLeakProfile : NSObject


/**
 开始记录内存分配堆栈，需要开启后才能进行检测。
 */
+ (void)startStackLogging;
    

/**
 停止记录内存分配堆栈
 */
+ (void)stopStackLogging;
    

/**
 执行一次泄露检测，建议在主线程调用，该操作会挂起所有子线程进行泄露检测（该操作较耗时，平均耗时在1s以上，请限制调用频率）
 */
+ (void)executeLeakCheck;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QAPMResourceMonitorProfile : NSObject

/**
 设置资源使用监控起始标记

 @param tag tag名称
 */
+ (void)setBeginTag:(NSString * __nonnull)tag;


/**
 设置资源使用监控结束标记

 @param tag tag名称
 */
+ (void)setStopTag:(NSString * __nonnull)tag;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

@interface QAPMCrashMonitorProfile : NSObject

/**
 Crash监控是否在运行

 @return YES or NO
 */
+ (BOOL)isRunnning;

@end

NS_ASSUME_NONNULL_END
