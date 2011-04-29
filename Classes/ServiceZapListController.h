//
//  ServiceZapListController.h
//  dreaMote
//
//  Created by Moritz Venn on 13.02.11.
//  Copyright 2011 Moritz Venn. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @brief Zap actions.

 @note Keep in sync with the row indices of the fully populated list.
 */
typedef enum
{
	zapActionRemote = 0,
	zapActionOPlayer = 1,
	zapActionOPlayerLite = 2,
	zapActionBuzzPlayer = 3,
	zapActionYxplayer = 4,
	zapActionMax = 5,
} zapAction;

@protocol ServiceZapListDelegate;

/*!
 @brief Table showing actions you can execute for a specific service.

 @note This table is used only on the iPad to make the UI more appealing, as a
 UIActionSheet (which is used on the iPhone) disturbs the ui flow too much while a popover
 appears more like a "side-action".
 @note For convenience reasons the iPhone uses this class to manage the action sheet too.
 */
@interface ServiceZapListController : UIViewController <UITableViewDelegate,
														UIActionSheetDelegate,
														UITableViewDataSource>
{
@private
	NSObject<ServiceZapListDelegate> *_zapDelegate; /*!< @brief Zap delegate. */
	BOOL hasAction[zapActionMax]; /*!< @brief Cache of supported zap actions */
	UIActionSheet *_actionSheet; /*!< @brief Action sheet if ran on iPhone/iPod Touch. */
}

/*!
 @brief Is the device able to play back a stream?
 Will return YES if a supported streaming-capable media player is installed.

 @return YES if streaming is possible, else NO.
 */
+ (BOOL)canStream;

/*!
 @brief Show Alert.
 Instead of a Table the iPhone uses an Alert Sheet to display the possible "zapping" methods.
 To reduce the possibility of errors by code duplication the sheet is managed in this class.

 @param delegate Delegate to be called back.
 @param tabBar Tab bar to show action sheet from.
 */
+ (ServiceZapListController *)showAlert:(NSObject<ServiceZapListDelegate> *)delegate fromTabBar:(UITabBar *)tabBar;

@property (nonatomic, retain) NSObject<ServiceZapListDelegate> *zapDelegate;

@end



/*!
 @brief Defines callbacks for this view.
*/
@protocol ServiceZapListDelegate
/*!
 @brief Selection was made.

 @param zapListController controller the selection was done in
 @param selectedAction action the user selected
 */
- (void)serviceZapListController:(ServiceZapListController *)zapListController selectedAction:(zapAction)selectedAction;
@end