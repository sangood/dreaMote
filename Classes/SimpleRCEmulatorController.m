//
//  SimpleRCEmulatorController.m
//  dreaMote
//
//  Created by Moritz Venn on 23.10.09.
//  Copyright 2009-2011 Moritz Venn. All rights reserved.
//

#import "SimpleRCEmulatorController.h"
#import "RemoteConnector.h"
#import "Constants.h"

#define SWIPE_MIN_DISPLACEMENT 10.0

@implementation SimpleRCEmulatorController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
	if((self = [super initWithNibName: @"SimpleRCEmulator" bundle: nil]))
	{
		//
	}
	return self;
}

- (void)viewDidLoad
{
	[self.view addSubview: self.rcView];
}

- (void)loadView
{
	CGRect frame;
	UIButton *roundedButtonType;
	const CGFloat factor = (IS_IPAD()) ? 2.0f : 1.0f;
	const CGFloat imageWidth = 135 * factor;
	const CGFloat imageHeight = 105 * factor;

	[super loadView];

	const CGSize mainViewSize = self.view.bounds.size;

	// create the rc views (i think its easier to have two views than to keep track of all buttons and add/remove them as pleased)
	frame = CGRectMake(0, 0, mainViewSize.width, mainViewSize.height);
	rcView = [[UIView alloc] initWithFrame: frame];
	[self.view addSubview:rcView];

	// TODO: we could add a volume slider too...

	// lame
	frame = CGRectMake(0, 0, imageWidth, imageHeight);
	roundedButtonType = [self newButton:frame withImage:@"exit.png" andKeyCode: kButtonCodeLame];
	[rcView addSubview: roundedButtonType];
	[roundedButtonType release];

	// menu
	frame = CGRectMake(mainViewSize.width - imageWidth, 0, imageWidth, imageHeight);
	roundedButtonType = [self newButton:frame withImage:@"menu.png" andKeyCode: kButtonCodeMenu];
	[rcView addSubview: roundedButtonType];
	[roundedButtonType release];

	// swipe
	frame = CGRectMake(0, 100, mainViewSize.width, mainViewSize.height - 145);
	roundedButtonType = [[UIButton alloc] initWithFrame: frame];
	roundedButtonType.userInteractionEnabled = NO;
	UIImage *image = [UIImage imageNamed:@"4-sided-arrow.png"];
	[roundedButtonType setBackgroundImage:image forState:UIControlStateHighlighted];
	[roundedButtonType setBackgroundImage:image forState:UIControlStateNormal];
	[rcView addSubview: roundedButtonType];
	[roundedButtonType release];
}

#pragma mark -
#pragma mark	Touch handling
#pragma mark -

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	const UITouch *touch = [[event allTouches] anyObject];
	lastLocation = [touch locationInView: self.view];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	const UITouch *touch = [[event allTouches] anyObject];
	const CGPoint location = [touch locationInView: self.view];
	const CGFloat xDisplacement = location.x - lastLocation.x;
	const CGFloat yDisplacement = location.y - lastLocation.y;
	const CGFloat xDisplacementAbs = (CGFloat)fabs(xDisplacement);
	const CGFloat yDisplacementAbs = (CGFloat)fabs(yDisplacement);

	// triple+ tap
	if([touch tapCount] > 2)
	{
		return;
	}
	// double tap
	if([touch tapCount] == 2)
	{
		[self sendButton: [NSNumber numberWithInteger: kButtonCodeOK]];
	}
	// horizontal swipe
	else if(xDisplacementAbs > yDisplacementAbs)
	{
		if(xDisplacementAbs <= SWIPE_MIN_DISPLACEMENT)
			return;

		// moved right?
		if(xDisplacement > 0.0)
		{
			[self sendButton: [NSNumber numberWithInteger: kButtonCodeRight]];
		}
		// moved left!
		else
		{
			[self sendButton: [NSNumber numberWithInteger: kButtonCodeLeft]];
		}
	}
	// vertical swipe
	else
	{
		if(yDisplacementAbs <= SWIPE_MIN_DISPLACEMENT)
			return;

		// moved down?
		if(yDisplacement > 0.0)
		{
			[self sendButton: [NSNumber numberWithInteger: kButtonCodeDown]];
		}
		// moved up!
		else
		{
			[self sendButton: [NSNumber numberWithInteger: kButtonCodeUp]];
		}
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	// TODO: anything?
	return;
}

@end
