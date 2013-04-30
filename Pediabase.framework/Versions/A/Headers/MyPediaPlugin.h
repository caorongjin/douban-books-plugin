
#import <Cocoa/Cocoa.h>

//The method that the delgate implements to be told about search results
@protocol PluginDelegate
- (void)searchReturnedNumberOfResults:(int)numberOfResults sender:(id)sender;
@end

/*
@protocol PediaPlugin
//This is the new plug-in search method, that includes options for limit, media and sorting
- (void)searchForString:(NSString *)aString limit:(NSInteger)aLimitNumber type:(NSInteger)mediaNumber sort:(NSInteger)sortNumber sender:(id)sender;

//This becomes the entry search, should only be a dictionary for entry, but it also works as a fallback for old plugins that handle "keyword" as the regular search
- (void)searchFor:(NSDictionary *)searchDict sender:(id)sender;
- (NSDictionary *)resultNumber:(int)number;

@optional
- (NSImage *)coverForEntry:(MOEntry *)anEntry;

- (void)downloadComplete:(NSString *)HTMLSource;
- (void)downloadDataComplete:(NSData *)someData;

- (void)openPreferences;

- (NSArray *)limits;
- (NSArray *)types;
- (NSArray *)sorts;
@end
 */

@protocol PediaPlugin
@optional
- (void)downloadDataComplete:(NSData *)someData;
- (void)openPreferences;
- (NSImage *)coverForEntry:(NSManagedObject *)anEntry;
- (NSString *)countryCode;
- (NSArray *)limits;
- (NSArray *)types;
- (NSArray *)sorts;
- (NSString *)placeHolder;
- (NSArray *)menuCommandFor:(NSArray *)selectedObjects;
- (NSDictionary *)detailsForPath:(NSString *)aString;
@end


@interface MyPediaPlugin : NSObject <PediaPlugin> {
	NSMutableArray *resultsTitles;
	NSMutableArray *resultsURLs;
		
	NSObject <PluginDelegate> *delegate;
	NSMutableData *receivedData;
	NSURLConnection *theConnection;	
}

//@property (readonly) NSMutableArray *resultsTitles;
//@property (retain, nonatomic) NSObject* delegate;

//Optional
//@property (readonly) NSString *countryCode;


//This is the new plug-in search method, that includes options for limit, media and sorting
- (void)searchForString:(NSString *)aString limit:(NSInteger)aLimitNumber type:(NSInteger)mediaNumber sort:(NSInteger)sortNumber sender:(id)sender;
//This becomes the entry search, should only be a dictionary for entry, but it also works as a fallback for old plugins that handle "keyword" as the regular search
- (void)searchFor:(NSDictionary *)searchDict sender:(id)sender;
- (NSDictionary *)resultNumber:(int)number;

- (NSArray *)resultsTitles;
- (NSObject*)delegate;
- (void)setDelegate:(NSObject <PluginDelegate> *)aDelegate;
- (void)cancelSearch;

//helper Methods
- (void)downloadWebPage:(NSString *)aWebPage;
- (void)downloadWebPage:(NSString *)aWebPage withPost:(NSString *)body encoding:(int)anEncoding;
- (void)downloadComplete:(NSString *)HTMLSource;

//### Old for compatability
- (void)setController:(id)aController;
//- (NSArray *)menuCommandFor:(NSArray *)selectedObjects;
@end

@protocol PediaPluginMandatory
+ (id)plugin;
@end

