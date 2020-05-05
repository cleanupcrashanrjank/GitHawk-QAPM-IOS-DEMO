//
//  QAPMUtilities.h
//  QAPM
//
//  Created by Cass on 2018/11/7.
//  Copyright © 2018 cass. All rights reserved.
//

#ifndef QAPMUtilities_h
#define QAPMUtilities_h

/**
 日志级别
 */
typedef NS_ENUM(NSInteger, QAPMLoggerLevel) {
    ///外发版本log
    QAPMLogLevel_Event,
    ///灰度和内部版本log
    QAPMLogLevel_Info,
    ///内部版本log
    QAPMLogLevel_Debug,
};

/**
 开启功能类型
 */
typedef NS_OPTIONS(NSUInteger, QAPMMonitorType) {
    
    QAPMMonitorTypeNone                     = 1 << 0,
    
    /// Blue(检测卡顿功能)
    QAPMMonitorTypeBlue                     = 1 << 1,
    
    /// Yellow(检测VC泄露功能)
    QAPMMonitorTypeYellow                   = 1 << 2,
    
    /**
     Sigkill(检测FOOM与卡死功能)
     开启后，会默认开启记录对象分配堆栈（会增加8%左右的cpu开销和10Mb内存）。
     更多设置请在 [QAPMConfig getInstance].sigkillConfig 中设置。
     为了保证数据的准确，请在Crash组件捕获到crash后调用: [QAPMSigkillProfile appDidCrashed];
     */
    QAPMMonitorTypeSigkill                  = 1 << 3,
    
    /**
     QQLeak(检测内存对象泄露功能)
     开启后，会记录对象分配的堆栈，不支持模拟器。
     执行检测一次检测请调用: [QAPMQQLeakProfile executeLeakCheck];
     执行一次泄露检测，建议在主线程调用，该操作会挂起所有子线程进行泄露检测（该操作较耗时，平均耗时在1s以上，请限制调用频率）。
     建议研发流程内使用。
     */
    QAPMMonitorTypeQQLeak                   = 1 << 4,
    
    /// 资源使用情况监控功能（每隔1s采集一次资源）
    QAPMMonitorTypeResourceMonitor          = 1 << 5,
    
    /// 内存最大使用值监控(触顶率)
    QAPMMonitorTypeMaxMemoryStatistic       = 1 << 6,
    
    /// 大块内存分配监控功能
    QAPMMonitorTypeBigChunkMemoryMonitor    = 1 << 7,
    
    /// 耗时打点统计功能
    QAPMMonitorTypeTimeStatistic            = 1 << 8,
    
    /// KSCrash监控功能
    QAPMMonitorTypeCrash                    = 1 << 9,

    /// 启动耗时监控功能
    /// QAPMMonitorTypeLaunchMonitor            = 1 << 10,
    
    /// HTTP监控功能(iOS10及以后可用)
    QAPMMonitorTypeHTTPMonitor              = 1 << 11,
    
    /// JSError
    QAPMMonitorTypeJSError                  = 1 << 12,
    
    /// Web Monitor (Web性能监控)
    QAPMMonitorTypeWebMonitor               = 1 << 13,
    
    /// 用户行为监控功能（需要导入相关SDK,参考文档）
    QAPMMonitorTypeIUPMonitor               = 1 << 14,
};

/**
 上报事件类型
 */
typedef NS_ENUM(NSInteger, QAPMUploadEventType) {
    /// 卡顿
    QAPMUploadEventTypeLAG                  = 0,
    /// VC泄露
    QAPMUploadEventTypeVCLeak               = 1,
    /// 触顶率
    QAPMUploadEventTypeCelingRate           = 2,
    /// 掉帧率
    QAPMUploadEventTypeDropFrameRate        = 3,
    /// Sigkill
    QAPMUploadEventTypeSigkill              = 4,
    /// 资源采集
    QAPMUploadEventTypeGatheringResource    = 5,
    /// 区间性能
    QAPMUploadEventTypeSectionPerformance   = 6,
    /// 对象泄露检测
    QAPMUploadEventTypeObjectLeak           = 7,
    /// 大块内存分配
    QAPMUploadEventTypeBigChunkMemory       = 8,
    /// 启动耗时上报
    QAPMUploadEventTypeUITime               = 9,
};

/**
 触发事件类型
 */
typedef NS_ENUM(NSInteger, QAPMEventType) {
    /// 卡顿
    QAPMEventTypeLAG                       = 0,
    /// VC泄露
    QAPMEventTypeVCLeak                    = 1,
    /// Sigkill
    QAPMEventTypeSigkill                   = 2,
    /// Normal crash
    QAPMEventTypeCrash                     = 3,
    /// 大块内存分配
    QAPMEventTypeBigChunkMemory            = 4,
};


/**
 监控功能状态
 */
typedef NS_ENUM(NSInteger, QAPMMonitorTypeState) {
    /// 用户未设置开启功能
    QAPMMonitorTypeStateUnSetting                = 0,
    /// 用户设置开启，等待获取后台配置中
    QAPMMonitorTypeStateWaittingServerConfig     = 1,
    /// 用户设置开启，但是后台配置不允许开启
    QAPMMonitorTypeStateServerNotAllow           = 2,
    /// 设置开启功能，但是未命中用户抽样率
    QAPMMonitorTypeStateMissSampleRate           = 3,
    /// 功能运行中或者可以使用
    QAPMMonitorTypeStateOpening                  = 4,
};

/**
 用于输出SDK调试log的回调
 */
typedef void(*QAPM_Log_Callback)(QAPMLoggerLevel level, const char* log);

/**
 功能开启时回调
 */
typedef void(*QAPMMonitorStartCallback)(QAPMMonitorType type);

/**
 用于输出上报事件
 */
typedef void(*QAPMUploadEventCallback)(NSString *eventId, NSTimeInterval eventTime, QAPMUploadEventType eventType);


/**
 触发事件时回调
 */
typedef NSString *(*QAPMEventCallback)(NSString *eventId, NSTimeInterval eventTime, QAPMEventType eventType);

extern QAPMUploadEventCallback uploadEventCallback;

extern QAPMMonitorStartCallback monitorStartCallback;

extern QAPMEventCallback qapmEventCallback;


#endif /* QAPMUtilities_h */
