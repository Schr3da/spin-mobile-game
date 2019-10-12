//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "OverviewContent.h"

@implementation OverviewContent
@synthesize title;
@synthesize value;
@synthesize color;
@synthesize imageName;

-(instancetype)init{
    self = [super init];
    if(self != nil){
        [self setDefaultValues];
    }
    return self;
}

-(void)setDefaultValues{
    self.title = nil;
    self.value = nil;
    self.imageName = nil;
    self.color = 0x000000;
}

-(void)dealloc{
    [super dealloc];
}

@end
