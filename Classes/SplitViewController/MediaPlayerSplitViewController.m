//
//  MediaPlayerSplitViewController.m
//  dreaMote
//
//  Created by Moritz Venn on 10.01.11.
//  Copyright 2011-2012 Moritz Venn. All rights reserved.
//

#import "MediaPlayerSplitViewController.h"

#import "PlayListController.h"
#import "MediaPlayerDetailsController.h"

@implementation MediaPlayerSplitViewController

- (id)init
{
    if((self = [super init]))
	{
		self.title = NSLocalizedString(@"MediaPlayer", @"Title of MediaPlayerSplitViewController");

		self.splitPosition = 512;
		UIImage *image = [UIImage imageNamed: @"mediaplayer.png"];
		self.tabBarItem.image = image;
    }
    return self;
}


#pragma mark -
#pragma mark UIViewController methods
#pragma mark -

- (void)loadView
{
    [super loadView];

	// Instantiate view controllers
	PlayListController *playListController = [[PlayListController alloc] init];
	MediaPlayerDetailsController *detailsController = [[MediaPlayerDetailsController alloc] init];
	detailsController.playlist = playListController.playlist;

	// Setup navigation controllers and add to split view
	UIViewController *navController1, *navController2;
	navController1 = [[UINavigationController alloc] initWithRootViewController: playListController];
	navController2 = [[UINavigationController alloc] initWithRootViewController: detailsController];
	self.viewControllers = [NSArray arrayWithObjects: navController1, navController2, nil];

	// Create "Clear" Button
	UIBarButtonItem *clearButton = [[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"Clear", @"Clear button/action in MediaPlayer")
																	style:UIBarButtonItemStyleBordered
																   target:detailsController
																   action:@selector(clearPlaylist:)];
	playListController.clearButton = clearButton;

	// Create "Save" Button
	UIBarButtonItem *saveButton = [[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"Save", @"Save button/action in MediaPlayer")
																	style:UIBarButtonItemStyleBordered
																   target:detailsController
																   action:@selector(savePlaylist:)];
	playListController.saveButton = saveButton;

	// Create "Load" Button
	UIBarButtonItem *loadButton = [[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"Load", @"Load button/action in MediaPlayer")
																   style:UIBarButtonItemStyleBordered
																  target:detailsController
																  action:@selector(showPlaylists:)];
	playListController.loadButton = loadButton;

	// add buttons
	UIBarButtonItem *flipItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
																			  target:detailsController
																			  action:@selector(flipView:)];
	const UIBarButtonItem *flexItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace
																					target:nil
																					action:nil];
	const UIBarButtonItem *deleteItem = [[UIBarButtonItem alloc] initWithCustomView:detailsController.deleteButton];
	NSArray *items = [[NSArray alloc] initWithObjects:deleteItem, clearButton, flexItem, saveButton, loadButton, detailsController.shuffleButton, nil];
	[playListController setToolbarItems:items animated:NO];
	[playListController.navigationController setToolbarHidden:NO animated:YES];
	playListController.navigationItem.leftBarButtonItem = flipItem;

	// details is delegate
	self.delegate = detailsController;

	// release allocated ressources
}

- (void)viewDidUnload
{
	self.delegate = nil;
	[super viewDidUnload];
}

@end
