//
//  HeaderView.h
//  spin
//
//  Created by schr3da on 29/03/15.
//
//
#import <UIKit/UIKit.h>

@interface SettingsCell : UITableViewCell{
    UILabel *titleL;
    UILabel *informationL;
    UILabel *descriptionL;
    UIImageView *imageV;
}

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier;
-(void)addComponents;
-(void)setImageNamed:(NSString *)filename;
-(void)setInformationLabelText:(NSString *)text;
-(void)setDescriptionLabelText:(NSString *)text;
-(void)setTitleText:(NSString *)text color:(UIColor *)color;

@end
