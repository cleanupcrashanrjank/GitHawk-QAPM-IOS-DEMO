//
//  QAPMCrashMonitorManager.h
//  QAPM
//
//  Created by Cass on 2019/4/11.
//  Copyright © 2019 cass. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QAPMCrashMonitorManager : NSObject

+ (instancetype)manager;

- (BOOL)start;

- (BOOL)isRunning;

@end

NS_ASSUME_NONNULL_END
