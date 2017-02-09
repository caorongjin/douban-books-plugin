/**
 * Copyright (c) 2017 Alexander Chow
 *
 * Douban Books Plugin is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Douban Books Plugin is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 */

#import <Cocoa/Cocoa.h>
#import "Constants.h"

#define FRAMEWORK_BUNDLE [NSBundle bundleWithIdentifier:@"com.bruji.pediabase"]

@class MOEntry, MOCollection;

@interface MyPluginManager : NSManagedObject 
- (void)addMenuItem:(NSMenuItem *)aMenuItem menuTitle:(NSString *)menuTitle;
@end

@interface MyFieldController : NSObject
- (NSString *)customFieldWithTitle:(NSString *)possibleTitle;
@end

@interface MyCollectionTableView : NSObject
- (MOCollection *)selectedCollection;
- (MOCollection *)borrowedCollection;
- (MOCollection *)wishlistCollection;
- (MOCollection *)libraryCollection;
- (NSArray *)allCollections;

// To select a collection use:
- (void)selectCollection:(MOCollection *)aCollection;

- (MOCollection *)createCollectionWithName:(NSString *)aName;
- (MOCollection *)createCollectionNamed:(NSString *)name withEntries:(NSSet *)aSet;
@end

// Plugin Controller 
@interface MyControllerForPlugins : NSObject
- (MKProgramType)programType;
- (NSManagedObject *)selectedEntry;
- (NSArray *)arrangedEntries;
- (NSArray *)selectedEntries;
- (MyFieldController *)fieldsController;
- (void)addEntriesWithAttributes:(NSArray *)entries;
- (NSString *)coverImagesPath;
- (MyPluginManager *)pluginManager;
- (MyCollectionTableView *)getCollections;

- (BOOL)addEntry:(MOEntry *)anEntry toCollection:(MOCollection *)aCollection;
@end

@interface MOEntry : NSManagedObject 
- (NSString *)coverImagePath;
- (void)addLinkWithAttributtes:(NSDictionary *)attributes;
@end

@interface MOLink : NSManagedObject 
- (void)deleteObject;
@end

@interface NSString (NSStringExtensions)
- (BOOL)isNotEmpty;
- (NSString *)stringByResolvingAliasInPath;

//Parsing
// Returns the first string that occurs between the given strings or nil if none do
- (NSString *)stringBetween:(NSString *)startString and:(NSString *)endString;
// Same as above but you can move the search to start at a given string, instead of the beginning
- (NSString *)stringBetween:(NSString *)startString and:(NSString *)endString startingFrom:(NSString *)primeString;
// Return an array of all the strings that occur between the given strings or nil if none do
- (NSArray *)stringsBetween:(NSString *)startString and:(NSString *)endString;


// html cleaning
- (NSString *)stringByCleaningHTML;
- (NSString *)stringByReplacingHTMLEncoding;
- (NSString *)stringByRemovingLeadingAndTrailingSpaces;
- (NSString *)stringByMovingEndingArticles;

- (BOOL)isEAN;

@end

@interface MyFunctionsShared : NSObject
+ (NSString *)flipAuthorFirstLast:(NSString *)anAuthor;
+ (NSString *)removeDashes:(NSString *)aString;
@end


#pragma mark -
@interface NSArray (NSArrayExtensions)
- (id)firstObject;
@end

#pragma mark -
@interface NSDate (NSDateExtensions)
- (NSCalendarDate *)dateAtBeginningOfDay;
- (NSCalendarDate *)dateAtEndOfDay;
- (NSCalendarDate *)dateAtBeginningOfYear;
- (BOOL)isNotEmpty;
@end