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

#define MyLog NSLog

//PROGRAM TYPES
enum {
	MKProgramDVDpedia = 1,
	MKProgramBookpedia,
	MKProgramCDpedia,
	MKProgramGamepedia
};
typedef NSUInteger MKProgramType;

#define A_MONTH_IN_SECONDS 2592000
#define A_WEEK_IN_SECONDS 604800
#define A_DAY_IN_SECONDS 86400

//#define MKOSXLeopard 0x00001050
#define MKOSXLeopard 5
#define MKOSXSnowLeopard 6
#define MKOSXLion 7

#define myPreferences [NSUserDefaults standardUserDefaults]

// http://bruji.com/howto/creating_templates/tags.html
// Key word that can be used for the details dictionary
// all program keywords
#define MKKeyEntryTitle @"title"
#define MKKeyEntryASIN @"asin"
#define MKKeyEntryDateAdded @"dateAdded"
#define MKKeyEntryMyRating @"myRating"
#define MKKeyEntryRelease @"releaseDate"
#define MKKeyEntryGenre @"genre"
#define MKKeyEntryCollection @"collectionID"
#define MKKeyEntryComments @"comments"
#define MKKeyEntryListPrice @"price"
#define MKKeyEntryPaidPrice @"PaidPrice"
#define MKKeyEntryPurcahsedAt @"purcahsedAt"
#define MKKeyEntryPurchasedOn @"purchasedOn"
#define MKKeyEntryBorrowedBy @"borrowedBy"
#define MKKeyEntryBorrowedOn @"borrowedOn"
#define MKKeyEntryDueDate @"dueDate"
#define MKKeyEntrySummary @"summary"
#define MKKeyEntryCustomOne @"custom1"
#define MKKeyEntryCustomTwo @"custom2"
#define MKKeyEntryCustomThree @"custom3"
#define MKKeyEntryCustomFive @"custom5"
#define MKKeyEntryCustomSix @"custom6"
#define MKKeyEntryCustomSeven @"custom7"
#define MKKeyEntryCustomEight @"custom8"
#define MKKeyEntryCustomNine @"custom9"
#define MKKeyEntryCustomTen @"custom10"

#define MKKeyEntryAwards @"awards"
//A URL starting with http: that leads to the details page
#define MKKeyEntryProductURL @"url"


//DVDpedia keywords
#define MKKeyDVDDirector @"director"
#define MKKeyDVDStudio @"studio"
#define MKKeyDVDTheatrical @"theatrical"
#define MKKeyDVDDuration @"duration"
#define MKKeyDVDStarring @"starring"
#define MKKeyDVDViewerRating @"rating"
#define MKKeyDVDAspectRatio @"aspectRatio"
#define MKKeyDVDSound @"sound"
#define MKKeyDVDVideoFormat @"videoFormat"
#define MKKeyDVDRated @"rated"
#define MKKeyDVDRegion @"region"
#define MKKeyDVDDiscs @"discs"
#define MKKeyDVDUPC @"upc"
#define MKKeyDVDWriter @"writer"
#define MKKeyDVDProducer @"producer"
#define MKKeyDVDLanguage @"languages"
#define MKKeyDVDSubtitles @"subtitles"
#define MKKeyDVDPictureFormat @"pictureFormat"
#define MKKeyDVDLastSeen @"lastSeen"
#define MKKeyDVDMedia @"media"
#define MKKeyDVDIMDB @"imdb"
#define MKKeyDVDCountry @"country"
#define MKKeyDVDFeatures @"features"
#define MKKeyDVDOriginalTitle @"originalTitle"

//Bookpedia
#define MKKeyBookAuthor @"author"
#define MKKeyBookAskingPrice @"askingPrice"
#define MKKeyBookBuyerName @"buyerName"
#define MKKeyBookBuyerEmail @"buyerEmail"
#define MKKeyBookBuyerAddress @"buyerAddress"
#define MKKeyBookReaderRating @"rating"
#define MKKeyBookChildrenReadingLevel @"children"
#define MKKeyBookCondition @"condition"
#define MKKeyBookDewey @"dewey"
#define MKKeyBookDimensions @"dimensions"
#define MKKeyBookEdition @"edition"
#define MKKeyBookEditor @"editor"
#define MKKeyBookFormat @"format"
#define MKKeyBookGift @"gift"
#define MKKeyBookIllustrator @"illustrator"
#define MKKeyBookLastRead @"lastRead"
#define MKKeyBookLCCN @"lccn"
#define MKKeyBookLocation @"location"
#define MKKeyBookISBN @"isbn"
#define MKKeyBookMarketPrice @"lowestNewPrice"
#define MKKeyBookPageMark @"pageMark"
#define MKKeyBookPages @"pages"
#define MKKeyBookPlacePublished @"placePublished"
#define MKKeyBookPlacedForSaleAt @"placedForSaleAt"
#define MKKeyBookPublisher @"publisher"
#define MKKeyBookSeries @"series"
#define MKKeyBookSoldOn @"soldOn"
#define MKKeyBookTranslator @"translator"
#define MKKeyBookNotes @"notes"
#define MKKeyBookSubjects @"subjects"
//NSNumber Bool YES or NO
#define MKKeyBookSigned @"signed"
#define MKKeyBookOnSale @"onSale"
#define MKKeyBookSoldBook @"hasBeenSold"


//CDpedia
#define MKKeyCDArtist @"artist"
#define MKKeyCDProducer @"producer"
#define MKKeyCDDuration @"duration"
#define MKKeyCDComposer @"composer"
#define MKKeyCDLabel @"label"
#define MKKeyCDCustomerRating @"rating"
#define MKKeyCDConductor @"conductor"
#define MKKeyCDDiscs @"discs"
#define MKKeyCDUPC @"upc"
#define MKKeyCDArrangedBy @"arrangedBy"
#define MKKeyCDMixedBy @"mixedBy"
#define MKKeyCDDiscID @"discID"
#define MKKeyCDCatalogNumber @"catalogNumber"
#define MKKeyCDFormat @"format"


//Gamepedia
#define MKKeyGameDeveloper @"developer"
#define MKKeyGamePlatform @"platform"
#define MKKeyGamePublisher @"publisher"
#define MKKeyGameScore @"score"
#define MKKeyGameRated @"rated"
#define MKKeyGamePlayerRating @"rating"
#define MKKeyGameTime @"time"
#define MKKeyGameSeries @"series"
#define MKKeyGameRegion @"region"
#define MKKeyGameDiscs @"discs"
#define MKKeyGameUPC @"upc"
#define MKKeyGameSystemRequirements @"systemRequirements"
#define MKKeyGameAchievements @"achievements"
#define MKKeyGameAwards @"awards"
#define MKKeyGameNumberOfPlayers @"numberOfPlayers"
#define MKKeyGameMulitplayer @"mulitplayer"
#define MKKeyGameLastPlayed @"lastPlayed"
#define MKKeyGameFeatures @"features"
//NSNumber Bool YES or NO
#define MKKeyGameNowPlaying @"nowPlaying"
#define MKKeyGameCompleted @"completed"
#define MKKeyGameManual @"manual"
#define MKKeyGameSpecialEdition @"specialEdition"


//Special Keywords
//An array of dictionaries with keys 'Name', 'URL', 'Type', 'Date' and 'Comments'
#define MKKeyEntryArrayLinks @"links"
#define MKKeyDVDArrayCredits @"credits"
#define MKKeyCDArrayTracks @"tracks"
// URL to the image
#define MKKeyEntryImageLocation @"imageLocation"

//These most both be of equal length as the first canme in Names corresponds tothe first role in Roles
#define MKKeyDVDArrayNames @"names"
#define MKKeyDVDArrayRoles @"roles"

//Same as above where they must be of equal length
#define MKKeyCDArraySongs @"songs"
#define MKKeyCDArrayDurations @"durations"
#define MKKeyCDArrayArtists @"artists"