/**
 * Copyright (c) 2013 Alexander Chow
 *
 * Douban Books Plugin is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Pingguo Dictionary is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 */

#import <Cocoa/Cocoa.h>

//The method that the delgate implements to be told about search results
@protocol PluginDelegate
- (void)searchReturnedNumberOfResults:(int)numberOfResults sender:(id)sender;
@end


@protocol PediaPlugin
@optional
- (void)downloadDataComplete:(NSData *)someData;
- (void)openPreferences;
- (NSString *)language;
- (NSImage *)coverForEntry:(NSManagedObject *)anEntry;
- (NSArray *)limits;
- (NSArray *)types;
- (NSArray *)sorts;
- (NSString *)countryCode;
@end
//http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
//http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2


@interface MyPediaPlugin : NSObject <PediaPlugin> {
	NSMutableArray *resultsTitles;
	NSMutableArray *resultsURLs;
		
	NSObject <PluginDelegate> *delegate;
	NSMutableData *receivedData;
	NSURLConnection *theConnection;	
}

//@property (readonly) NSMutableArray *resultsTitles;
//@property (retain, nonatomic) id delegate;

//This is the new plug-in search method, that includes options for limit, media and sorting
- (void)searchForString:(NSString *)aString limit:(NSInteger)aLimitNumber type:(NSInteger)mediaNumber sort:(NSInteger)sortNumber sender:(id)sender;

//This becomes the entry search, should only be a dictionary for entry, but it also works as a fallback for old plugins that handle "keyword" as the regular search
- (void)searchFor:(NSDictionary *)searchDict sender:(id)sender;
- (NSDictionary *)resultNumber:(int)number;

- (NSArray *)resultsTitles;
- (NSObject*)delegate;
- (void)setDelegate:(NSObject *)aDelegate;


//helper Methods
- (void)downloadWebPage:(NSString *)aWebPage;
- (void)downloadWebPage:(NSString *)aWebPage withPost:(NSString *)body encoding:(int)anEncoding;
- (void)downloadComplete:(NSString *)HTMLSource;

@end