//
//  EventListController.h
//  dreaMote
//
//  Created by Moritz Venn on 09.03.08.
//  Copyright 2008-2011 Moritz Venn. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "EventSourceDelegate.h"
#import "ReloadableListController.h"
#import "ServiceZapListController.h" /* ServiceZapListDelegate */

// Forward declarations...
@protocol ServiceProtocol;
@class EventViewController;
@class CXMLDocument;

/*!
 @brief Event List.
 
 Lists events and opens an EventViewController upon selection.
 */
@interface EventListController : ReloadableListController <UITableViewDelegate,
													UITableViewDataSource,
													EventSourceDelegate,
													UIScrollViewDelegate,
													UIPopoverControllerDelegate,
													UIActionSheetDelegate,
													ServiceZapListDelegate>
{
@protected
	NSMutableArray *_events; /*!< @brief Event List. */
	NSObject<ServiceProtocol> *_service; /*!< @brief Current Service. */
	NSDateFormatter *_dateFormatter; /*!< @brief Date Formatter. */
	UIPopoverController *popoverController; /*!< @brief Popover controller */

	CXMLDocument *_eventXMLDoc; /*!< @brief Event XML Document. */
	EventViewController *_eventViewController; /*!< @brief Cached Event Detail View. */
}

/*!
 @brief Open new Event List for given Service.
 
 @param ourService Service to display Events for.
 @return EventListController instance.
 */
+ (EventListController*)forService: (NSObject<ServiceProtocol> *)ourService;



/*!
 @brief Service.
 */
@property (nonatomic, retain) NSObject<ServiceProtocol> *service;

/*!
 @brief Date Formatter.
 */
@property (nonatomic, retain) NSDateFormatter *dateFormatter;

/*!
 @brief Popover Controller.
 */
@property (nonatomic, retain) UIPopoverController *popoverController;

@end
