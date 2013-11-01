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

#ifdef DEBUG
	#define DLog NSLog
#else
	#define DLog( s, ... )
#endif

#define SEARCH_URL_PREFACE @"http://book.douban.com/subject_search?search_text=%@"

#import "DoubanBooks.h"
#import "Constants.h"

@implementation DoubanBooks

- (NSString *)countryCode {
	return @"CN";
}

- (void)downloadComplete:(NSString *)HTMLSource {

	// Search the page and create a list of book titles and URLs for the detailed information

	NSArray * subjectItems = [HTMLSource stringsBetween:@"class=\"subject-item\">" and:@"</li>"];

	for (NSString * subjectItem in subjectItems) {
		NSString * entry = [subjectItem stringBetween:@"<h2" and:@"</h2>"];

		NSString * url = [entry stringBetween:@"href=\"" and:@"\""];

		NSString * title = [[entry stringBetween:@"title=\"" and:@"\""] stringByCleaningHTML];

		if (url && title) {
			[resultsTitles addObject:title];
			[resultsURLs addObject:url];
		}
	}

	[delegate searchReturnedNumberOfResults:[resultsURLs count] sender:self];
}

- (NSString *)languageCode {
	return @"zh";
}

- (NSDictionary *)resultNumber:(int)number {

	// Get the details for one of the results and return it as a dictionary

	NSMutableDictionary * resultsDict = [NSMutableDictionary dictionary];

	if (number >= [resultsURLs count]) {
		NSLog(@"Error: Request out of range: %d of %d", number, [resultsURLs count]);

		[resultsDict setObject:@"No data found from Douban" forKey:@"title"];

		return resultsDict;
	}

	NSString * detailsURLString = [resultsURLs objectAtIndex:number];

	NSURL * detailsURL = [NSURL URLWithString:detailsURLString];

	NSURLRequest * theRequest = [NSURLRequest requestWithURL:detailsURL cachePolicy:NSURLRequestUseProtocolCachePolicy
											 timeoutInterval:15.0];

	NSData * data = [NSURLConnection sendSynchronousRequest:theRequest returningResponse:nil error:nil];

	NSString * html = [[[NSString alloc] initWithData:data  encoding:NSUTF8StringEncoding] autorelease];

	if (html == nil) {
		return nil;
	}

	// Valid details URL

	DLog(@"Details URL: %@", detailsURLString);

	[resultsDict setObject:detailsURLString forKey:@"url"];
	[resultsDict setObject:[resultsTitles objectAtIndex:number] forKey:@"title"];
	[resultsDict setValue:[self countryCode] forKey:@"locale"];
	[resultsDict setValue:[self languageCode] forKey:@"localeLanguage"];

	// Image

	NSString * mainpicDiv = [html stringBetween:@"id=\"mainpic\"" and:@"</div>"];

	if (mainpicDiv) {
		NSString * imageURLString = [mainpicDiv stringBetween:@"href=\"" and:@"\""];

		if (imageURLString) {
			[resultsDict setObject:imageURLString forKey:MKKeyEntryImageLocation];
		}
	}

	// Info

	NSString * infoDiv = [html stringBetween:@"id=\"info\"" and:@"</div>"];

	if (infoDiv) {
		[self setResult:resultsDict infoDiv:infoDiv];
	}

	// Summary

	NSString * introDiv = [html stringBetween:@"class=\"intro\"" and:@"<style>"];

	if (introDiv) {
		[resultsDict setObject:[introDiv stringBetween:@"<p>" and:@"</p>"] forKey:MKKeyEntrySummary];
	}

	return resultsDict;
}

- (void)searchFor:(NSDictionary *)searchDict sender:(id)sender {
	if ([searchDict objectForKey:@"keyword"] != nil) {
		[self searchForString:[searchDict objectForKey:@"keyword"] limit:0 type:0 sort:0 sender:sender];
	}
	else if ([searchDict objectForKey:MKKeyBookISBN] != nil) {
		[self searchForString:[searchDict objectForKey:MKKeyBookISBN] limit:0 type:0 sort:0 sender:sender];
	}
	else if ([searchDict objectForKey:MKKeyEntryTitle] != nil) {
		[self searchForString:[searchDict objectForKey:MKKeyEntryTitle] limit:0 type:0 sort:0 sender:sender];
	}
	else {
		[sender searchReturnedNumberOfResults:0 sender:self];
	}
}

- (void)searchForString:(NSString *)string limit:(NSInteger)aLimitNumber type:(NSInteger)typeNumber
				   sort:(NSInteger)sortNumber sender:(id)sender {

	self.delegate = sender;

	[resultsTitles removeAllObjects];
	[resultsURLs  removeAllObjects];
	
	NSMutableString * searchString = [NSMutableString stringWithString:string];

	[searchString replaceOccurrencesOfString:@" " withString:@"+" options:NSLiteralSearch
									   range:NSMakeRange(0, [searchString length])];

	NSString * encodedString = [searchString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
	NSString * searchURL = [NSString stringWithFormat:SEARCH_URL_PREFACE, encodedString];

	DLog(@"Search URL: %@", searchURL);
	
	[self downloadWebPage:searchURL];
}

- (void)setResult:(NSMutableDictionary *)resultsDict infoDiv:(NSString*)infoDiv {

	// Basic information

	[self setResult:resultsDict infoDiv:infoDiv start:@"出版社:</span>" forKey:MKKeyBookPublisher];
	[self setResult:resultsDict infoDiv:infoDiv start:@"出版年:</span>" forKey:MKKeyEntryRelease];
	[self setResult:resultsDict infoDiv:infoDiv start:@"定价:</span>" forKey:MKKeyEntryListPrice];
	[self setResult:resultsDict infoDiv:infoDiv start:@"页数:</span>" forKey:MKKeyBookPages];
	[self setResult:resultsDict infoDiv:infoDiv start:@"ISBN:</span>" forKey:MKKeyBookISBN];

	// Author(s)

	NSString * authorSpan = [infoDiv stringBetween:@"作者</span>:" and:@"</span>"];

	if (authorSpan) {
		NSArray * authors = [authorSpan stringsBetween:@"\">" and:@"</a>"];

		if (authors) {
			[resultsDict setObject:authors forKey:MKKeyBookAuthor];
		}
	}

	// Translator(s)

	NSString * translatorSpan = [infoDiv stringBetween:@"译者</span>:" and:@"</span>"];

	if (translatorSpan) {
		NSArray * translators = [translatorSpan stringsBetween:@"\">" and:@"</a>"];

		if (translators) {
			[resultsDict setObject:translators forKey:MKKeyBookTranslator];
		}
	}

	// Series

	NSString * seriesSpan = [infoDiv stringBetween:@"丛书:</span>" and:@"<br>"];

	if (seriesSpan) {
		NSString * series = [[seriesSpan stringBetween:@"\">" and:@"</a>"] stringByCleaningHTML];

		if (series) {
			[resultsDict setObject:series forKey:MKKeyBookSeries];
		}
	}
}

- (void)setResult:(NSMutableDictionary *)resultsDict infoDiv:(NSString*)infoDiv start:(NSString *)start
		   forKey:(NSString*)key {

	NSString * result = [[infoDiv stringBetween:start and:@"<br/>"] stringByCleaningHTML];

	if (result) {
		if ([key isEqualToString:MKKeyEntryListPrice]) {
			result = [result stringByReplacingOccurrencesOfString:@"元" withString:@""];
			result = [result stringByReplacingOccurrencesOfString:@"¥" withString:@""];
			result = [result stringByReplacingOccurrencesOfString:@"RMB" withString:@""];

			NSMutableString *mutableResult = [NSMutableString stringWithString:result];

			[mutableResult insertString:@"¥" atIndex:0];

			result = [NSString stringWithString:mutableResult];
		}
		else if ([key isEqualToString:MKKeyBookPages]) {
			result = [result stringByReplacingOccurrencesOfString:@"页" withString:@""];
		}

		[resultsDict setObject:result forKey:key];
	}
}

@end