//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//
#import <UIKit/UIKit.h>

@interface OverviewContent : NSObject{
}

-(instancetype)init;

@property (readwrite, assign, nonatomic) NSString *title;
@property (readwrite, assign, nonatomic) NSString *value;
@property (readwrite, assign, nonatomic) NSString *imageName;
@property (readwrite, assign, nonatomic) int color;

@end
