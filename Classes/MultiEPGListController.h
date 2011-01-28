//
//  MultiEPGListController.h
//  dreaMote
//
//  Created by Moritz Venn on 27.01.11.
//  Copyright 2011 Moritz Venn. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ReloadableListController.h"

#import "EPGCache.h"
#import "EventSourceDelegate.h"
#import "MBProgressHUD.h" /* MBProgressHUDDelegate */
#import "ServiceSourceDelegate.h"

// forward declare
@class CXMLDocument;
@protocol MultiEPGDelegate;

/*!
 @brief MultiEPG Controller.
 Provides MultiEPG including all management Code.

 @todo Reconsider implementing this as a view, because this is pretty much what we use of it.
 */
@interface MultiEPGListController : ReloadableListController <UITableViewDelegate,
															UITableViewDataSource,
															EPGCacheDelegate,
															EventSourceDelegate,
															MBProgressHUDDelegate,
															ServiceSourceDelegate>
{
@private
	EPGCache *_epgCache; /*!< @brief EPGCache Singleton. */
	NSObject<MultiEPGDelegate> *_mepgDelegate;
	NSObject<ServiceProtocol> *_bouquet; /*!< @brief Current Bouquet. */
	NSMutableArray *_services; /*!< @brief List of services. */
	CXMLDocument *_serviceXMLDocument; /*!< @brief Current Service XML-Document. */
	NSMutableDictionary *_events; /*!< @brief Dictionary (service sref) -> (event list). */
	NSDate *_curBegin; /*!< @brief Current begin of timespan. */
	MBProgressHUD *progressHUD; /*!< @brief Progress Hud. */
	NSInteger pendingRequests; /*!< @brief Pending requests. */
}

/*!
 @brief Bouquet.
 */
@property (nonatomic, retain) NSObject<ServiceProtocol> *bouquet;

/*!
 @brief MultiEPG Delegate.
 */
@property (nonatomic, retain) NSObject<MultiEPGDelegate> *multiEpgDelegate;

@end



/*!
 @brief Delegate for MultiEPG List.
 */
@protocol MultiEPGDelegate
/*!
 @brief Event was selected in Multi EPG.

 @param multiEPG MultiEPG the selection was made in.
 @param event Event selected.
 @param service Service event is on.
 */
- (void)multiEPG:(MultiEPGListController *)multiEPG didSelectEvent:(NSObject<EventProtocol> *)event onService:(NSObject<ServiceProtocol> *)service;
@end