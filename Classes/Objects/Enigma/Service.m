//
//  Service.m
//  dreaMote
//
//  Created by Moritz Venn on 08.03.08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "Service.h"

#import "../Generic/Service.h"
#import "CXMLElement.h"

@implementation EnigmaService

- (NSString *)sref
{
	NSArray *resultNodes = [_node nodesForXPath:@"reference" error:nil];
	for(CXMLElement *currentChild in resultNodes)
	{
		return [currentChild stringValue];
	}
	return nil;
}

- (void)setSref: (NSString *)new
{
	[NSException raise:@"ExcUnsopportedFunction" format:nil];
}

- (NSString *)sname
{
	NSArray *resultNodes = [_node nodesForXPath:@"name" error:nil];
	for(CXMLElement *currentChild in resultNodes)
	{
		return [currentChild stringValue];
	}
	return nil;
}

- (void)setSname: (NSString *)new
{
	[NSException raise:@"ExcUnsopportedFunction" format:nil];
}

- (id)initWithNode: (CXMLNode *)node
{
	if (self = [super init])
	{
		_node = [node retain];
	}
	return self;
}

- (void)dealloc
{

	[super dealloc];
}

- (BOOL)isValid
{
	return _node && self.sref != nil;
}

- (NSArray *)nodesForXPath: (NSString *)xpath error: (NSError **)error
{
	if(!_node)
		return nil;

	return [_node nodesForXPath: xpath error: error];
}

#pragma mark -
#pragma mark	Copy
#pragma mark -

- (id)copyWithZone:(NSZone *)zone
{
	id newElement = [[Service alloc] initWithService: self];

	return newElement;
}

- (NSString *)description
{
	return [NSString stringWithFormat:@"<%@> Name: '%@'.\n Ref: '%@'.\n", [self class], self.sname, self.sref];
}

@end