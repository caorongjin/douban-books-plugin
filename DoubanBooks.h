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

#import <Foundation/Foundation.h>
#import "MyControllerForPlugins.h"
#import "MyPediaPlugin.h"

@interface DoubanBooks : MyPediaPlugin {
}

- (void)setResult:(NSMutableDictionary *)resultsDict infoDiv:(NSString*)infoDiv;
- (void)setResult:(NSMutableDictionary *)resultsDict infoDiv:(NSString*)infoDiv start:(NSString *)start
		   forKey:(NSString*)key;

@end