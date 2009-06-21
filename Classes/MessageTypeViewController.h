//
//  MessageTypeViewController.h
//  dreaMote
//
//  Created by Moritz Venn on 17.10.08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

// Forward declaration
@protocol MessageTypeDelegate;

/*!
 @brief Message Type Selector.
 
 Allows to choose the type of a message to be send to the STB.
 */
@interface MessageTypeViewController : UIViewController <UITableViewDelegate,
														UITableViewDataSource>
{
@private
	NSInteger _selectedItem; /*!< @brief Selected Item. */
	id<MessageTypeDelegate> _delegate; /*!< @brief Delegate. */
}

/*!
 @brief Standard constructor.
 
 @param typeKey Selected message type.
 @return MessageTypeViewController instance.
 */
+ (MessageTypeViewController *)withType: (NSInteger) typeKey;

/*!
 @brief Set Delegate.
 
 The delegate will be called back when disappearing to inform it about the newly selected
 message type.
 
 @param delegate New delegate object.
 */
- (void)setDelegate: (id<MessageTypeDelegate>) delegate;



/*!
 @brief Selected Item.
 */
@property (nonatomic) NSInteger selectedItem;

@end



/*!
 @brief MessageTypeViewController Delegate.
 
 Implements callback functionality for MessageTypeViewController.
*/
@protocol MessageTypeDelegate <NSObject>

/*!
 @brief Type was selected.
 
 @param newType Selected type.
 */
- (void)typeSelected: (NSNumber *) newType;

@end
