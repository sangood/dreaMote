//
//  BouquetListController.h
//  dreaMote
//
//  Created by Moritz Venn on 02.01.09.
//  Copyright 2008-2011 Moritz Venn. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "ReloadableListController.h"
#import "ServiceSourceDelegate.h"
#import "SimpleSingleSelectionListController.h" /* SimpleSingleSelectionListDelegate */

typedef enum
{
	LIST_TYPE_BOUQUETS,
	LIST_TYPE_PROVIDER,
} bouquetListType;

// Forward declaration
@class BaseXMLReader;
@class ServiceListController;
@protocol BouquetListDelegate;
@protocol ServiceListDelegate;

/*!
 @brief Bouquet list.
 
 Display list of known bouquets and start ServiceListController on selected ones.
 */
@interface BouquetListController : ReloadableListController <UITableViewDelegate,
															UITableViewDataSource,
															ServiceSourceDelegate,
															UIAlertViewDelegate,
															UIActionSheetDelegate,
															SimpleSingleSelectionListDelegate>
{
@private
	NSMutableArray *_bouquets; /*!< @brief Bouquet List. */
	NSObject<ServiceListDelegate, UIAppearanceContainer> __unsafe_unretained *_serviceDelegate; /*!< @brief Service Delegate. */
	NSObject<BouquetListDelegate, UIAppearanceContainer> __unsafe_unretained *_bouquetDelegate; /*!< @brief Bouquet Delegate. */
	BOOL _refreshBouquets; /*!< @brief Refresh Bouquet List on next open? */
	BOOL _isRadio; /*!< @brief Are we in radio mode? */
	bouquetListType _listType; /*!< @brief Show bouquet or provider list? */
	BOOL _isSplit; /*!< @brief Split mode? */
	ServiceListController *_serviceListController; /*!< @brief Caches Service List instance. */
	UIBarButtonItem *_radioButton; /*!< @brief Radio/TV-mode toggle */
	UIPopoverController *popoverController; /*!< @brief Popover */

	BaseXMLReader *_xmlReader; /*!< @brief Bouquet XML. */
}

/*!
 @brief Bouquet Delegate.
 */
@property (nonatomic, unsafe_unretained) NSObject<BouquetListDelegate, UIAppearanceContainer> *bouquetDelegate;

/*!
 @brief Service Selection Delegate.

 This Function is required for Timers as they will use the provided Callback when you change the
 Service of a Timer.
 */
@property (nonatomic, unsafe_unretained) NSObject<ServiceListDelegate, UIAppearanceContainer> *serviceDelegate;

/*!
 @brief Currently in radio mode?
 */
@property (nonatomic) BOOL isRadio;

/*!
 @brief Controlled by a split view controller?
 */
@property (nonatomic) BOOL isSplit;

/*!
 @brief Service List
 */
@property (nonatomic, strong) IBOutlet ServiceListController *serviceListController;

/*!
 @brief View will reapper.
 */
@property (nonatomic) BOOL willReappear;

@end



/*!
 @brief Delegate for BouquetListController.

 Objects wanting to be called back by a BouquetListController need to implement this Protocol.
 */
@protocol BouquetListDelegate <NSObject>

/*!
 @brief Bouquet was selected.

 @param newBouquet Bouquet that was selected.
 */
- (void)bouquetSelected:(NSObject<ServiceProtocol> *)newBouquet;

@end
