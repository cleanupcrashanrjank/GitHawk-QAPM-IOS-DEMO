//
//  AppDelegate.swift
//  Freetime
//
//  Created by Ryan Nystrom on 4/30/17.
//  Copyright © 2017 Ryan Nystrom. All rights reserved.
//

import UIKit
import Alamofire
import AlamofireNetworkActivityIndicator
import Fabric
import Crashlytics
import GitHubSession

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?
    private let flexController = FlexController()
    private let appController = AppController()

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {

        appController.appDidFinishLaunching(with: window)

        // setup fabric
        Fabric.with([Crashlytics.self])

        // send rating prompt app load event
        RatingController.applicationDidLaunch()

        // setup FLEX
        flexController.configureWindow(window)

        // use Alamofire status bar network activity helper
        NetworkActivityIndicatorManager.shared.isEnabled = true

        // setup UIAppearance overrides
        Styles.setupAppearance()

        // setup app icon badging
        BadgeNotifications.configure(application: application)

        // log device environment information
        LogEnvironmentInformation(application: application)

        // setup content size category change handler
        UIContentSizeCategoryChangeHandler.shared.setup()

         /// Setting the log output
         QAPM.registerLogCallback { (_ level:QAPMLoggerLevel, log:UnsafePointer<Int8>?) in
             let sdata = String(cString:log!)
             print(sdata)
             //print(String(format: "log info:%s", s_data))
         }

         let multipleOptions: QAPMMonitorType = [.blue, .sigkill,.resourceMonitor, .maxMemoryStatistic, .yellow, .timeStatistic, .qqLeak]
         QAPMConfig.getInstance().enableMonitorTypeOptions = multipleOptions
             /*
             QAPMMonitorType(rawValue: QAPMMonitorType.blue.rawValue | QAPMMonitorType.yellow.rawValue | QAPMMonitorType.sigkill.rawValue | QAPMMonitorType.qqLeak.rawValue | QAPMMonitorType.resourceMonitor.rawValue | QAPMMonitorType.maxMemoryStatistic.rawValue | QAPMMonitorType.maxMemoryStatistic.rawValue | QAPMMonitorType.timeStatistic.rawValue)
        */
         QAPMConfig.getInstance().host = "https://qapm.qq.com"
         QAPMConfig.getInstance().blueConfig.sampleRate = 1
         QAPMConfig.getInstance().yellowConfig.sampleRate = 1
         QAPMConfig.getInstance().sigkillConfig.sampleRate = 1
         QAPMConfig.getInstance().resourceMonitorConfig.sampleRate = 1
         QAPMConfig.getInstance().maxMemoryStatisticConfig.sampleRate = 1
         QAPMConfig.getInstance().bigChunkMemoryMonitorConfig.sampleRate = 1
         QAPMConfig.getInstance().qqleakConfig.sampleRate = 1
         QAPMConfig.getInstance().timeStatisticConfig.sampleRate = 1


         QAPMConfig.getInstance().userId = "189272879"
         QAPMConfig.getInstance().customerAppVersion = "v1.1"

         /// 启动QAPM
         QAPM.start(withAppKey: "{appkey}")
        
        return true
    }

    func application(_ application: UIApplication, performActionFor shortcutItem: UIApplicationShortcutItem, completionHandler: @escaping (Bool) -> Void) {
        appController.router.handle(path: shortcutItem.type, params: shortcutItem.params)
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        appController.appDidBecomeActive()
    }

    func application(_ application: UIApplication, performFetchWithCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
        appController.performFetch(application: application, with: completionHandler)
    }

    func application(_ app: UIApplication, open url: URL, options: [UIApplicationOpenURLOptionsKey: Any] = [:]) -> Bool {
        return appController.router.handle(url: url).wasHandled
    }

}
