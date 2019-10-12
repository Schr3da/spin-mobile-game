//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import <UIKit/UIKit.h>

@interface SettingsContent : NSObject{

}

-(instancetype)init;

@property (readwrite, assign, nonatomic) NSString *title;
@property (readwrite, assign, nonatomic) NSString *information;
@property (readwrite, assign, nonatomic) NSString *selectedImageName;
@property (readwrite, assign, nonatomic) NSString *unselectedImageName;
@property (readwrite, assign, nonatomic) bool selected;
@property (readwrite, assign, nonatomic) int color;


@end
