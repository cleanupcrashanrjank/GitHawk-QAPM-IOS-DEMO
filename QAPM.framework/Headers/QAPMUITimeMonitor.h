//
//  QAPMUITimeMonitor.h
//  QAPM
//
//  Created by Cass on 2019/5/11.
//  Copyright © 2019 cass. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QAPMUITimeMonitor : NSObject

+ (instancetype)shared;

/**
 设置Debug模式，Debug模式下连接Xcode也会进行上报启动耗时，默认为NO.
 由于Debug下Xcode可能会额外加载一些动态库，导致启动耗时不准确，建议不调试进行上报数据。
 */
@property (nonatomic, assign) BOOL debugEnable;

/**
 【必须调用API】开始启动耗时统计，请在Main函数开始调用时设置。
 */
- (void)start;

/**
 【必须调用API】请在AppDidFinishLaunch开始调用时设置。
 */
- (void)setAppDidFinishLaunchBeginTimestamp;

/**
 【必须调用API】请在第一个页面ViewDidApppear开始调用时设置。
 */
- (void)setFirtstViewDidApppearTimestamp;

/**
 设置自定义打点区间开始，该区间需要在启动时间区间内。begin与end的scene需要一致。
 当设置了 setFirtstViewDidApppearTimestamp 后，后面设置的自定义打点区间将不会被统计。
 
 @param scene 场景名
 */
- (void)setBeginTimestampForScene:(NSString *)scene;

/**
 设置自定义打点区间结束，该区间需要在启动时间区间内。begin与end的scene需要一致。
 当设置了 setFirtstViewDidApppearTimestamp 后，后面设置的自定义打点区间将不会被统计。
 
 @param scene 场景名
 */
- (void)setEndTimestampForScene:(NSString *)scene;

/**
 设置首次启动和冷启动的启动时间阈值，当超过此阈值会被认为此次启动为慢启动，并上报个例数据。
 个例数据中包括自定义打点区间、SDK打点区间和启动堆栈（堆栈采集功能被命中抽样才会有堆栈数据）。
 
 @param threshold 默认4000ms
 */
- (void)setSlowLaunchThreshold:(NSTimeInterval)threshold;

/**
 设置开启采集堆栈抽样因子，按概率进行开启堆栈采集。
 
 @param factor 例如设置1/10抽样，则设置fatctor = 10。默认为100。
 */
- (void)setStackSampleFactor:(uint32_t)factor;

@end

NS_ASSUME_NONNULL_END
